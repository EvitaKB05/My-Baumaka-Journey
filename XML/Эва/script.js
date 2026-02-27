// файл script.js
window.onload = function () {
    const loginScreen = document.getElementById('loginScreen');
    const calculator = document.getElementById('calculator');
    const loginButton = document.getElementById('loginButton');

    // Показываем окно входа при загрузке страницы
    // Исполaьзуем flexbox

    loginButton.onclick = showCalculator;


    document.addEventListener('keydown', function (event) {
        if (event.key === ' ') {
            showCalculator();
        }
    });
    function showLogin(){
        loginScreen.style.display = 'flex'; 
    }
    function showCalculator() {
        loginScreen.style.display = 'none';
        calculator.style.display = 'block';
        initializeCalculator();
    }
   /* function hideCalculator(){
        document.getElementById('calculator').style.display = 'none';
    }
    document.getElementById('description-tub').addEventListener('click', hideCalculator);
    */
    document.getElementById("btn_digit_000").onclick = function() {
        if (a === '') return;
        if (selectedOperation !== null && a !== '0') {
            a = a * 1000;
            outputElement.innerHTML = a.toString;
        }


    }
    let a = '0'
    let b = ''
    let expressionResult = ''
    let selectedOperation = null

    // окно вывода результата
    outputElement = document.getElementById("result")
    history_string = document.getElementById("calculation-history");
    // список объектов кнопок циферблата (id которых начинается с btn_digit_)
    digitButtons = document.querySelectorAll('[id ^= "btn_digit_"]')

    function onDigitButtonClicked(digit) {
        if (a == '0' && digit == '.'){
            a = '0.'
        }
        if (!selectedOperation) {
            if (((digit != '.') || (digit == '.' && !a.includes(digit))) && a!='0') { 
                a += digit
            }
            else if (((digit != '.') || (digit == '.' && !a.includes(digit)) )&& a=='0') { 
                    a = digit
            }
            if (a == '000') { a = '0';}
            outputElement.innerHTML = a
        } else {
            if ((digit != '.') || (digit == '.' && !b.includes(digit))) { 
                b += digit
                outputElement.innerHTML = b        
            }
        }
    }

    // устанавка колбек-функций на кнопки циферблата по событию нажатия
    digitButtons.forEach(button => {
        button.onclick = function () {
            const digitValue = button.innerHTML
            onDigitButtonClicked(digitValue)
        }
    });
        
    document.getElementById  ("btn_op_sign").onclick = function () {
        if (a === '') return
        if (a != 0) {
            expressionResult = (+a) * (-1);
        }
        a = expressionResult.toString();
        selectedOperation = null;
        outputElement.innerHTML = a;
    }
    // установка колбек-функций для кнопок операций
    document.getElementById("btn_op_mult").onclick = function () {
        if (a === '') return
        selectedOperation = 'x'
    }
    document.getElementById("btn_op_plus").onclick = function () {
        if (a === '') return
        selectedOperation = '+'
    }
    document.getElementById("btn_op_minus").onclick = function () {
        if (a === '') return
        selectedOperation = '-'
    }
    document.getElementById("btn_op_div").onclick = function () {
        if (a === '') return
        selectedOperation = '/'
    }
    document.getElementById("btn_op_percent").onclick = function() {
        if (a === '') return
        selectedOperation = '%'
    }
    document.getElementById("btn_op_sq").onclick = function () {
        if (a === '') return
        expressionResult = (+a) * (+a)
        a = expressionResult.toString();
        b = ''
        selectedOperation = null
        outputElement.innerHTML = a;
    }
    document.getElementById("btn_op_fact").onclick = function () {
        if (a === '') return
        let num = parseInt(a)
        if (isNaN(num) || num < 0) {
            expressionResult = 'Error'
        }
        else if (num === 0) {
            expressionResult = 1
        }
        else if (num < 10000) {
            expressionResult = 1
            for (let i = 1; i <= num; i++) {
                expressionResult *= i
            }
        }
        else {
            expressionResult = "Слишком многа :("
        }
        a = expressionResult.toString();
        b = '';
        selectedOperation = null;
        outputElement.innerHTML = a;
    }
    document.getElementById("btn_op_sqrt").onclick = function () {
        if (a === '') return
        if (+a < 0) {
            expressionResult = 'Error'
        }
        else {
            expressionResult = Math.sqrt(+a)
        }
        a = expressionResult.toString();
        selectedOperation = null;
        outputElement.innerHTML = a;
    }
    document.getElementById("log-in-button").addEventListener("click", showLogin);
    // кнопка очищения
    document.getElementById("btn_op_clear").onclick = function () {
        a = ''
        b = ''
        selectedOperation = null
        expressionResult = ''
        outputElement.innerHTML = 0
    }
    document.getElementById("btn_op_backspace").onclick = function () {
        if (!selectedOperation) {
            a = a.slice(0, -1);
            outputElement.innerHTML = a || '0'; // Show 0 if a is empty
            if( a === '-'){
                a = '0';
                outputElement.innerHTML = a; 
            }
        } else {
            b = b.slice(0, -1);
            outputElement.innerHTML = b || '0'; // Show 0 if b is empty
        }
    }
    // кнопка расчёта результата
    document.getElementById("btn_op_equal").onclick = function () {
        if (a === '' || b === '' || !selectedOperation)
            return

        history_string.innerHTML = a + selectedOperation + b + "=";

        switch (selectedOperation) {
            case 'x':
                expressionResult = (+a) * (+b)
                break;
            case '+':
                expressionResult = (+a) + (+b)
                break;
            case '-':
                expressionResult = (+a) - (+b)
                break;
            case '/':
                expressionResult = (+a) / (+b)
                break;
            case '%':
                expressionResult = (+a) * (+b) / 100
                break;
        }

        a = expressionResult.toString()
        history_string.innerHTML += a;
        b = ''
        selectedOperation = null
        outputElement.innerHTML = a
    }
};