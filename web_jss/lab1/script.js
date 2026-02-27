// файл script.js
window.onload = function(){ 
    const loginScreen = document.getElementById('loginScreen');
    const calculator = document.getElementById('calculator');
    const loginButton = document.getElementById('loginButton');

    // Показываем окно входа при загрузке страницы
    loginScreen.style.display = 'flex'; // Исполaьзуем flexbox

    loginButton.onclick = showCalculator;


    document.addEventListener('keydown', function(event) {
        if (event.key === ' ') {
            showCalculator();
        }
    });

    function showCalculator() {
        loginScreen.style.display = 'none';
        calculator.style.display = 'block';
        initializeCalculator();
    }
    
/*
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
        button.onclick = function() {
            const digitValue = button.innerHTML
            onDigitButtonClicked(digitValue)
        }
    });
    
    // установка колбек-функций для кнопок операций
    document.getElementById("btn_op_mult").onclick = function() { 
        if (a === '') return
        selectedOperation = 'x'
    }
    document.getElementById("btn_op_plus").onclick = function() { 
        if (a === '') return
        selectedOperation = '+'
    }
    document.getElementById("btn_op_minus").onclick = function() { 
        if (a === '') return
        selectedOperation = '-'
    }
    document.getElementById("btn_op_div").onclick = function() { 
        if (a === '') return
        selectedOperation = '/'
    }

    
    // кнопка очищения
    document.getElementById("btn_op_clear").onclick = function() { 
        a = ''
        b = ''
        selectedOperation = ''
        expressionResult = ''
        outputElement.innerHTML = 0
    }
    // кнопка процента
    document.getElementById("btn_op_percent").onclick = function() {
        if (a === '') return
        if (b !== '') {
            calculateResult()
        }
        selectedOperation = '%'
    }
    // кнопка квадрат
    document.getElementById("btn_op_sq").onclick = function(){
        if (a === '') return
        selectedOperation = 'x²'
    }
    // кнопка факториал
    document.getElementById("btn_op_fact").onclick = function(){
        if (a === '') return
        selectedOperation = 'x!'
    }
    // кнопка квадратный корень
    document.getElementById("btn_op_sqrt").onclick = function() {
        if (a === '') return
        selectedOperation = '√'
    }
    

    // кнопка расчёта результата
    document.getElementById("btn_op_equal").onclick = function() { 
        if (a === '' || b === '' || !selectedOperation)
            return
            
        switch(selectedOperation) { 
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
                expressionResult = (+a) / 100 * (+b)
                break;
            case 'x²':
                expressionResult = (+a) * (+a)
                break;
            case 'x!':
                expressionResult = factorial(+a)
                break;
            case '√':
                expressionResult = Math.sqrt(+a)
                break;
        }
        
        a = expressionResult.toString()
        b = ''
        selectedOperation = null
    
        outputElement.innerHTML = a
    }
    };
*/ 
}