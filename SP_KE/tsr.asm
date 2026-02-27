; =======================================
;  tsr.asm
;  Сборка:
;  > tasm.exe /l tsr.asm
;  > tlink /t /x tsr.obj
; =======================================

code segment 'code'
    assume  CS:code, DS:code
    org 100h

_start:
    jmp _initTSR                                ; на начало программы

    ; Данные программы
    ignoreEnabled               DB 0            ; флаг функции замены прописных на строчные
    translateFrom               DB 'KVYJG'      ; заменяемые символы
    translateTo                 DB 'ЛМНОП'      ; символы, на которые будет происходить замена
    translateLength             DB 5            ; длина строки translateFrom
    translateEnabled            DB 0            ; флаг функции перевода

    signaturePrintingEnabled    DB 0            ; флаг вывода подписи
    counter                     DW 0
    printDelay                  EQU 7           ; задержка перед выводом "подписи" в секундах

    ; Данные для вывода подписи (полная таблица как на изображении)
    signatureLineLength         DW  52
    signatureLine1              DB  179, 'Трундаев Д. В.                                      ', 179
    signatureLine2              DB  179, 'ИУ5-42Б                                             ', 179
    signatureLine3              DB  179, 'Вариант: #18                                         ', 179
    tableTop                    DB  218, 50 dup (196), 191
    tableBottom                 DB  192, 50 dup (196), 217

    helpMsg     DB '> tsr.com [/?]' , 10, 13
                DB ' [/?] - вывод данной справки', 10, 13
                DB ' выгрузка резидента при повторном запуске без параметров', 10, 13
                DB '  F6  - вывод ФИО и группы по таймеру (7 сек.) в центре экрана', 10, 13
                DB '  F7  - включение/отключения курсивного вывода русского символа П', 10, 13
                DB '  F8  - включение/отключение частичной русификации клавиатуры: KVYJG -> ЛМНОП', 10, 13
                DB '  F9  - включение/отключение режима замены прописных букв на строчные', 10, 13, '$'

    commandLineResult           DB 0

    cursiveEnabled              DB 0            ; флаг перевода символа в курсив
    cursiveSymbol               DB 00000000b    ; символ, составленный из единиц (его курсивный вариант)
                                DB 00000000b
                                DB 00000000b
                                DB 01111111b
                                DB 01111111b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 01100011b
                                DB 00000000b
                                DB 00000000b
                                DB 00000000b

    charToCursiveIndex          DB 'П'          ; символ для замены
    savedSymbol                 DB 16 dup(0FFh) ; переменная для хранения старого символа

    ; Адреса старых обработчиков прерываний
    old_int9hOffset             DW  ?
    old_int9hSegment            DW  ?
    old_int1ChOffset            DW  ?
    old_int1ChSegment           DW  ?
    old_int2FhOffset            DW  ?
    old_int2FhSegment           DW  ?

    ; Сообщения программы
    installedMsg                DB  'Резидент загружен.$'
    alreadyInstalledMsg         DB  'Резидент уже был загружен.$'
    removedMsg                  DB  'Резидент выгружен из памяти.$'
    noRemoveMsg                 DB  'Не удалось выгрузить резидент.$'

    true                        EQU 0FFh

    ; Новый обработчик прерывания клавиатуры (int 9h)
    new_int9h proc far
        push SI AX BX CX DX ES DS
        push CS
        pop DS

        pushf
        call dword ptr CS:[old_int9hOffset]
        mov AX, 40h
        mov ES, AX
        mov BX, ES:[1Ch]
        sub BX, 2h
        cmp BX, 1Eh
        jae _go
        mov BX, 3Ch
    _go:
        mov DX, ES:[BX]

        ; Обработка функциональных клавиш
        cmp DH, 40h                             ; F6
        jne _F7
        not signaturePrintingEnabled
        mov ES:[1Ch], BX
        jmp _quit
    _F7:
        cmp DH, 41h                             ; F7
        jne _F8
        mov ES:[1Ch], BX
        not cursiveEnabled
        call toggleCursive
        jmp _quit
    _F8:
        cmp DH, 42h                             ; F8
        jne _F9
        not translateEnabled
        mov ES:[1Ch], BX
        jmp _quit
    _F9:
        cmp DH, 43h                             ; F9
        jne _translateOrIgnore
        not ignoreEnabled
        mov ES:[1Ch], BX
        jmp _quit

    _translateOrIgnore:
        cmp ignoreEnabled, true
        jne _checkTranslate
        
        cmp DL, 'A'
        jb _checkTranslate
        cmp DL, 'Z'
        ja _checkTranslate
        add DL, 20h
        mov ES:[BX], DX
        jmp _quit

    _checkTranslate:
        cmp translateEnabled, true
        jne _quit

        mov SI, 0
        mov CL, translateLength
    _checkTranslateLoop:
        cmp DL, translateFrom[SI]
        je _translate
        inc SI
        loop _checkTranslateLoop
        jmp _quit

    _translate:
        xor AX, AX
        mov AL, translateTo[SI]
        mov ES:[BX], AX

    _quit:
        pop DS ES DX CX BX AX SI
        iret
    new_int9h endp

    ; Процедура переключения курсива
    toggleCursive proc
        push ES AX BX CX DX BP
        push CS
        pop ES

        cmp cursiveEnabled, true
        jne _restoreSymbol

        call saveFont
        mov BP, BX
        mov BL, charToCursiveIndex
        xor BH, BH
        mov CX, 16
        mul CX
        add BX, AX

        push DS
        push ES
        pop DS
        lea DI, savedSymbol
        mov SI, BX
        mov CX, 16
        rep movsb
        pop DS

        mov CX, 1
        mov DX, word ptr charToCursiveIndex
        lea BP, cursiveSymbol
        call changeFont
        jmp _exitToggleCursive

    _restoreSymbol:
        mov CX, 1
        mov DX, word ptr charToCursiveIndex
        lea BP, savedSymbol
        call changeFont

    _exitToggleCursive:
        pop BP DX CX BX AX ES
        ret
    toggleCursive endp

    ; Процедуры работы с шрифтами
    changeFont proc
        push AX BX
        mov AX, 1100h
        mov BX, 1000h
        int 10h
        pop BX AX
        ret
    changeFont endp

    saveFont proc
        push AX BX
        mov AX, 1130h
        mov BX, 0600h
        int 10h
        pop BX AX
        ret
    saveFont endp

    ; Обработчик прерывания мультиплексора (int 2Fh)
    new_int2Fh proc
        cmp AH, 0FFh
        jne _2Fh_default
        cmp AL, 0
        je  _alreadyInstalled2Fh
        cmp AL, 1
        je  _uninstall
        jmp _2Fh_default

    _2Fh_default:
        jmp dword ptr CS:[old_int2FhOffset]

    _alreadyInstalled2Fh:
        mov AH, 'i'
        iret

    _uninstall:
        push DS ES
        mov AX, 2509h
        mov DX, word ptr CS:old_int9hOffset
        mov DS, word ptr CS:old_int9hSegment
        int 21h

        mov AX, 251Ch
        mov DX, word ptr CS:old_int1ChOffset
        mov DS, word ptr CS:old_int1ChSegment
        int 21h

        mov AX, 252Fh
        mov DX, word ptr CS:old_int2FhOffset
        mov DS, word ptr CS:old_int2FhSegment
        int 21h

        mov ES, CS:2Ch
        mov AH, 49h
        int 21h
        jc _notRemove

        push CS
        pop ES
        mov AH, 49h
        int 21h
        jc _notRemove

        mov DX, offset removedMsg
        mov AH, 09h
        int 21h
        jmp _2Fh_exit

    _notRemove:
        mov DX, offset noRemoveMsg
        mov AH, 09h
        int 21h

    _2Fh_exit:
        pop ES DS
        iret
    new_int2Fh endp

    ; Обработчик прерывания таймера (int 1Ch)
    new_int1Ch proc far
        push AX DS
        push CS
        pop DS

        pushf
        call dword ptr CS:[old_int1ChOffset]

        cmp signaturePrintingEnabled, true
        jne _notToPrint

        cmp counter, printDelay*18
        jb _dontPrint

        mov signaturePrintingEnabled, 0
        mov counter, 0
        call printSignature

    _dontPrint:
        inc counter

    _notToPrint:
        pop DS AX
        iret
    new_int1Ch endp

    ; Процедура вывода строки подписи
    printSignatureLine proc
        push DX
        mov CX, signatureLineLength
        mov BL, 0111b
        mov AX, 1301h
        int 10h
        pop DX
        inc DH
        ret
    printSignatureLine endp

    ; Процедура вывода всей подписи (полная таблица)
    printSignature proc
        push AX DX CX BX ES BP

        mov AH, 03h
        int 10h
        push DX

        mov DX, 0C0Fh
        mov AH, 0Fh
        int 10h

        push CS
        pop ES

        lea BP, tableTop
        call printSignatureLine
        lea BP, signatureLine1
        call printSignatureLine
        lea BP, signatureLine2
        call printSignatureLine
        lea BP, signatureLine3
        call printSignatureLine
        lea BP, tableBottom
        call printSignatureLine

        pop DX
        mov AH, 02h
        int 10h

        pop BP ES BX CX DX AX
        ret
    printSignature endp

    ; Основная процедура инициализации
    _initTSR:
        call commandParamsParser
        cmp commandLineResult, 2
        je _exit

        mov AH, 0FFh
        mov AL, 0
        int 2Fh
        cmp AH, 'i'
        je _checkUninstall

        ; Установка нового обработчика прерываний
        mov AX, 3509h
        int 21h
        mov word ptr CS:old_int9hOffset, BX
        mov word ptr CS:old_int9hSegment, ES
        mov AX, 2509h
        mov DX, offset new_int9h
        int 21h

        mov AX, 351Ch
        int 21h
        mov word ptr CS:old_int1ChOffset, BX
        mov word ptr CS:old_int1ChSegment, ES
        mov AX, 251Ch
        mov DX, offset new_int1Ch
        int 21h

        mov AX, 352Fh
        int 21h
        mov word ptr CS:old_int2FhOffset, BX
        mov word ptr CS:old_int2FhSegment, ES
        mov AX, 252Fh
        mov DX, offset new_int2Fh
        int 21h

        mov DX, offset installedMsg
        mov AH, 09h
        int 21h

        mov DX, offset _initTSR
        int 27h

    _checkUninstall:
        ; Проверка на необходимость выгрузки (если программа запущена без параметров)
        cmp commandLineResult, 0
        jne _exit

        ; Выгрузка резидентной части
        mov AH, 0FFh
        mov AL, 1
        int 2Fh
        jmp _exit

    _alreadyInstalled:
        mov DX, offset alreadyInstalledMsg
        mov AH, 09h
        int 21h

    _exit:
        mov AX, 4C00h
        int 21h

    ; Парсер командной строки
    commandParamsParser proc
        push SI
        mov SI, 80h
        lodsb
        or AL, AL
        jz _paramParsingEnd

    _nextChar:
        lodsb
        cmp AL, ' '
        je _nextChar
        cmp AL, 0Dh
        je _paramParsingEnd
        cmp AL, '/'
        jne _paramParsingEnd

        lodsb
        cmp AL, '?'
        je _displayHelp
        jmp _paramParsingEnd

    _displayHelp:
        mov DX, offset helpMsg
        mov AH, 09h
        int 21h
        mov commandLineResult, 2

    _paramParsingEnd:
        pop SI
        ret
    commandParamsParser endp

code ends
end _start