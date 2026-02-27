// файл script.js
window.onload = function () {
    const loginScreen = document.getElementById('loginScreen');
    const calculator = document.getElementById('calculator');
    const loginButton = document.getElementById('loginButton');

    // Показываем окно входа при загрузке страницы
    loginScreen.style.display = 'flex'; // Исполaьзуем flexbox

    loginButton.onclick = showCalculator;


    document.addEventListener('keydown', function (event) {
        if (event.key === ' ') {
            showCalculator();
        }
    });

    function showCalculator() {
        loginScreen.style.display = 'none';
        calculator.style.display = 'block';
        initializeCalculator();
    }
    document.getElementById('description-button').addEventListener('click', hideCalculator);
    let a = ''
    let b = ''
    let expressionResult = ''
    let selectedOperation = null

    // окно вывода результата
    outputElement = document.getElementById("result")

    // список объектов кнопок циферблата (id которых начинается с btn_digit_)
    digitButtons = document.querySelectorAll('[id ^= "btn_digit_"]')

    function onDigitButtonClicked(digit) {
        if (!selectedOperation) {
            if ((digit != '.') || (digit == '.' && !a.includes(digit))) {
                a += digit
            }
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
        else {
            expressionResult = 1
            for (let i = 1; i <= num; i++) {
                expressionResult *= i
            }
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
        b = ''
        selectedOperation = null
        outputElement.innerHTML = a
    }
};