export class AuthorPage{

    constructor(parent){
        this.parent = parent
    }

    getHTML(){
        return(`
            <!-- Responsive navbar-->
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container px-4 px-lg-5">
                    <a class="navbar-brand">Об авторе</a>
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
                    </div>
                </div>
            </nav>
            <!-- Header - set the background image for the header in the line below-->
            <header class="py-5 bg-image-full" style="background-image: url('https://source.unsplash.com/wfh8dDlNFOk/1600x900')">
                <div class="text-center my-5">
                    <img class="img-fluid rounded-circle mb-4" src="assets/ava.png" alt="..." />
                    <h1 class="text-white fs-3 fw-bolder">Full Width Pics</h1>
                    <p class="text-white-50 mb-0">Landing Page Template</p>
                </div>
            </header>
            <!-- Content section-->
            <section class="py-5">
                <div class="container my-5">
                    <div class="row justify-content-center">
                        <div class="col-lg-6">
                            <h2>Жуков Никита Отабек Угли</h2>
                            <p class="lead">Группа: ИУ5-42Б</p>
                            <p class="mb-0"><a class="nav-link" href="https://github.com/Dominuszz">Перейти на GitHub</a></p>
                        </div>
                    </div>
                </div>
            </section>
            <!-- Footer-->
            <footer class="py-5 bg-dark">
                <div class="container"><p class="m-0 text-center text-white">Copyright &copy; Your Website 2023</p></div>
            </footer>
            <!-- Bootstrap core JS-->
            <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>
            <!-- Core theme JS-->
            <script src="js/scripts.js"></script>`)
    }

    addRef(id_name, listener){
        document.getElementById(id_name).addEventListener("click", listener)
    }

    render(listener){
        this.parent.innerHTML = this.getHTML()
        listener()
    }
}