export class CalcPage{
    constructor(parent){
        this.parent = parent
    }

    getHTML(){
        return(`
            <!-- Navigation-->
        <nav class="navbar navbar-expand-lg navbar-light bg-light">
            <div class="container px-4 px-lg-5">
                <a class="navbar-brand">Калькулятор</a>
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation"><span class="navbar-toggler-icon"></span></button>
                <div class="collapse navbar-collapse" id="navbarSupportedContent">
                    <ul class="navbar-nav me-auto mb-2 mb-lg-0 ms-lg-4">
                        <li class="nav-item"><a class="nav-link active" aria-current="page" id="main">Главная</a></li>
                        <li class="nav-item"><a class="nav-link" id="calc">Калькулятор</a></li>
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false">Информация</a>
                            <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                                <li><a class="dropdown-item" id="lab">Все лабы</a></li>
                                <li><hr class="dropdown-divider" /></li>
                                <li><a class="dropdown-item" id="author">Об авторе</a></li>
                            </ul>
                        </li>
                    </ul>
                    <form class="d-flex">
                    </form>
                </div>
            </div>
        </nav>
        <!-- Header-->
        <header class="bg-dark py-5">
            <div class="container px-4 px-lg-5 my-5">
                <div class="text-center text-white">
                    <h1 class="display-4 fw-bolder">Калькулятор</h1>
                    <p class="lead fw-normal text-white-50 mb-0">Специально для подсчётов</p>
                </div>
            </div>
        </header>
        <!-- Section-->
       
        <div class="divForCalc">
            <div id="calcbody" class="calcbody">
              <!-- div - это базовый html-контейнер, который может содержать в себе другие html-элементы. -->
    
              <!-- блок с экраном калькулятора, где будет выводиться результат вычислений. -->
              <div id="result" class="result">
                0
              </div>
    
              <!-- блок с кнопками калькулятора. -->
              <div>
                <!--горизонтальный ряд из четырех кнопок-->
                <div>
                  <button id="btn_op_clear" class="my-btn secondary">C</button>
                  <button id="btn_op_sign" class="my-btn secondary">+/-</button>
                  <button id="btn_op_percent" class="my-btn secondary">%</button>
                  <button id="btn_op_div" class="my-btn secondary">/</button>
                </div>
    
                <div>
                  <button id="btn_digit_7" class="my-btn">7</button>
                  <button id="btn_digit_8" class="my-btn">8</button>
                  <button id="btn_digit_9" class="my-btn">9</button>
                  <button id="btn_op_mult" class="my-btn primary">x</button>
                </div>
    
                <div>
                  <button id="btn_digit_4" class="my-btn">4</button>
                  <button id="btn_digit_5" class="my-btn">5</button>
                  <button id="btn_digit_6" class="my-btn">6</button>
                  <button id="btn_op_minus" class="my-btn primary">-</button>
                </div>
    
                <div>
                  <button id="btn_digit_1" class="my-btn">1</button>
                  <button id="btn_digit_2" class="my-btn">2</button>
                  <button id="btn_digit_3" class="my-btn">3</button>
                  <button id="btn_op_plus" class="my-btn primary">+</button>
                </div>
    
                <div>
                  <button id="btn_digit_0" class="my-btn">0</button>
                  <button id="btn_digit_000" class="my-btn">000</button>
                  <button id="btn_digit_dot" class="my-btn">.</button>
                  <button id="btn_op_backspace" class="my-btn primary">⌫</button>
                </div>
                <div>
                  <button id="btn_op_fact" class="my-btn primary">x!</button>
                  <button id="btn_op_sqrt" class="my-btn primary">√</button>
                  <button id="btn_op_sqr" class="my-btn primary">x²</button>
                  <button id="btn_op_topowerof" class="my-btn primary">xʸ</button>
                </div>
                <div>
                  <button id="btn_op_equal" class="my-btn primary execute">=</button>
                </div>
    
              </div>
    
            </div>
            <div class="divForBtn">
                <button class="btn_theme" id="btn_theme_toggle">Сменить тему</button>
                <button class="btn_theme" id="btn_result_change">Сменить цвет результата</button>
            </div>
          </div>


        <!-- Footer-->
        <footer class="py-5 bg-dark">
            <div class="container"><p class="m-0 text-center text-white">Copyright &copy; Веб-сайт для лабораторной 2025</p></div>
        </footer>
        <!-- Bootstrap core JS-->
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>
        <!-- Core theme JS-->
        <script src="js/scripts_calc.js"></script>`)
    }

    render(listener){
        this.parent.innerHTML = this.getHTML()
        this.start()
        listener()
    }

    updateResult(value) {
        const resultElement = document.getElementById("result");
        const maxLength = 10;
    
        const numericValue = parseFloat(value);
    
        if (value.toString().length > maxLength) {
            resultElement.textContent = numericValue.toExponential(2);
        } 
        else {
            
            resultElement.textContent = value;
        }
    }

    fact(num) {
        if (num == 0) {
            return 1;
        }
        else {
            return num * this.fact(num - 1);
        }
    }

    onDigitButtonClicked(digit) {

        if (!this.selectedOperation) {
            if ((digit != '.') || (digit == '.' && !a.includes(digit))) {
                this.a += digit
            }

            this.updateResult(this.a);
        } else {
            if ((digit != '.') || (digit == '.' && !b.includes(digit))) {
                this.b += digit
                this.updateResult(this.b);
            }
        }
    }

    start(){
    this.a = ''
    this.b = ''
    this.expressionResult = ''
    this.selectedOperation = null
    this.justCalculated = false;
    // окно вывода результата
    this.outputElement = document.getElementById("result")

    // список объектов кнопок циферблата (id которых начинается с btn_digit_)
    this.digitButtons = document.querySelectorAll('[id ^= "btn_digit_"]')


    // устанавка колбек-функций на кнопки циферблата по событию нажатия
    this.digitButtons.forEach(button => {
        button.onclick = () => {
            const digitValue = button.innerHTML
            this.onDigitButtonClicked(digitValue)
        }
    });

    // установка колбек-функций для кнопок операций
    document.getElementById("btn_op_mult").onclick = () => {
        if (this.a === '') return
        if (this.justCalculated) {
            this.b = '';
            this.justCalculated = false;
        }
        this.selectedOperation = 'x'
    }
    document.getElementById("btn_op_plus").onclick = () => {
        if (this.a === '') return;
        if (this.justCalculated) {
            this.b = '';
            this.justCalculated = false;
        }
        else if (this.b !== '') {
            this.a = (+this.a) + (+this.b);
            this.updateResult(this.a);
            this.b = '';
        }

        this.selectedOperation = '+';

    }
    //document.getElementById("font").onchange = () =>  {
    //    const selectedFont = this.value;
    //    document.body.style.fontFamily = selectedFont;
    //};
    document.getElementById("btn_result_change").onclick = () =>  {
        const resultElement = document.getElementById("result");
        const colors = ["red", "blue", "green", "yellow"];
        const currentColor = resultElement.classList[1];
        let nextColor = colors[0];
        if (currentColor) {
            const currentIndex = colors.indexOf(currentColor);
            nextColor = colors[(currentIndex + 1) % colors.length];
        }

        // Удаляем все классы цветов и добавляем новый
        resultElement.classList.remove("red", "blue", "green", "yellow");
        resultElement.classList.add(nextColor);
    }
    document.getElementById("btn_theme_toggle").onclick = () =>  {
        document.body.classList.toggle("light-theme");
    };

    document.getElementById("btn_op_minus").onclick = () => {
        if (this.a === '') return;
        if (this.justCalculated) {
            this.b = '';
            this.justCalculated = false;
        }
        else if (this.b !== '') {
            this.a = (+this.a) - (+this.b);
            this.updateResult(this.a);
            this.b = '';
        }

        this.selectedOperation = '-';
    }
    document.getElementById("btn_op_div").onclick = () => {
        if (this.a === '') return
        if (this.justCalculated) {
            this.b = '';
            this.justCalculated = false;
        }
        this.selectedOperation = '/'
    }

    // кнопка очищения
    document.getElementById("btn_op_clear").onclick =() =>  {
        this.a = ''
        this.b = ''
        this.selectedOperation = ''
        this.expressionResult = ''
        this.outputElement.innerHTML = 0
    }

    document.getElementById("btn_op_sign").onclick = () =>  {

        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = (this.a * (-1)).toString()
                this.updateResult(this.a)
            }
        }
        else {
            if (this.b !== '') {
                this.b = (this.b * (-1)).toString()
                this.updateResult(this.b)
            }
        }
    }

    document.getElementById("btn_op_percent").onclick = () =>  {

        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = (this.a /= 100).toString()
                this.updateResult(this.a)
            }
        }
        else {
            if (this.b !== '') {
                this.b = (this.b /= 100).toString()
                this.updateResult(b)
            }
        }
    }

    document.getElementById("btn_op_topowerof").onclick = () =>  {
        if (this.a === '') return
        if (this.justCalculated) {
            this.b = '';
            this.justCalculated = false;
        }
        this.selectedOperation = '^'
    }

    document.getElementById("btn_op_sqrt").onclick = () =>  {

        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = (Math.sqrt(this.a)).toString()
                this.updateResult(this.a)
            }
        }
        else {
            if (this.b !== '') {
                this.b = (Math.sqrt(this.b)).toString()
                this.updateResult(this.b)
            }
        }
    }
    document.getElementById("btn_op_sqr").onclick = () =>  {

        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = (Math.pow(this.a, 2)).toString()
                this.updateResult(this.a)
            }
        }
        else {
            if (this.b !== '') {
                this.b = (Math.pow(this.b, 2)).toString()
                this.updateResult(this.b)
            }
        }
    }
    document.getElementById("btn_op_fact").onclick = () =>  {

        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = (this.fact(this.a)).toString()
                this.updateResult(this.a)
            }
        }
        else {
            if (this.b !== '') {
                this.b = (this.fact(this.b)).toString()
                this.updateResult(this.b)
            }
        }
    }

    document.getElementById("btn_op_backspace").onclick = () =>  {
        if (!this.selectedOperation || (this.selectedOperation && this.justCalculated)) {
            if (this.a !== '') {
                this.a = this.a.slice(0, -1)
                if(this.a!='')this.updateResult(this.a)
                else this.outputElement.innerHTML = '0' 
            }
        }
        else {
            if (this.b !== '') {
                this.b = this.b.slice(0, -1)
                if(this.b!='')this.updateResult(this.b)
                else this.outputElement.innerHTML = '0' 
            }
        }
    }
    // кнопка расчёта результата
    document.getElementById("btn_op_equal").onclick = () =>  {
        if (this.a === '' || this.b === '' || !this.selectedOperation)
            return

        switch (this.selectedOperation) {
            case 'x':
                this.expressionResult = (+this.a) * (+this.b)
                break;
            case '+':
                this.expressionResult = (+this.a) + (+this.b)
                break;
            case '-':
                this.expressionResult = (+this.a) - (+this.b)
                break;
            case '/':
                this.expressionResult = (+this.a) / (+this.b)
                break;
            case '^':
                this.expressionResult = Math.pow((+this.a), (+this.b))
                break;
        }

        this.a = this.expressionResult.toString()
        this.updateResult(this.a)
        this.justCalculated = true
    }

    document.addEventListener('keydown', (event) => {
            const key = event.key;

            if (/[0-9.]/.test(key)) {
                onDigitButtonClicked(key);
            }

            switch (key) {
                case '+':
                    document.getElementById("btn_op_plus").click();
                    break;
                case '-':
                    document.getElementById("btn_op_minus").click();
                    break;
                case '*':
                    document.getElementById("btn_op_mult").click();
                    break;
                case '/':
                    document.getElementById("btn_op_div").click();
                    break;
                case 'Enter':
                    document.getElementById("btn_op_equal").click();
                    break;
                case 'Backspace':
                    document.getElementById("btn_op_backspace").click();
                    break;
                case 'Escape':
                    document.getElementById("btn_op_clear").click();
                    break;
                case '^':
                    document.getElementById("btn_op_topowerof").click();
                    break;
                case '!':
                    document.getElementById("btn_op_fact").click();
                    break;
                case '%':
                    document.getElementById("btn_op_percent").click();
                    break;
                case '@':
                    document.getElementById("btn_op_sqrt").click();
                    break;
                case 'q':
                    document.getElementById("btn_op_sqr").click();
                    break;
                case 'CapsLock':
                    document.getElementById("btn_op_sign").click();
                    break;
                
            }
        })
    }
}