import { ajax } from "../../modules/ajax.js"
import { stockUrls } from "../../modules/stockUrls.js"

export class ButtonComponent {
    constructor(parent, id) {
        this.parent = parent;
        this.id = id;
    }

    getData(listener) {
        ajax.get(stockUrls.getStockById(this.id), (data) => {
            if (data) {
                this.renderData(data, listener);
            }
        });
    }

    renderData(item, listener) {
        document.getElementById("cat-name").innerHTML = item.name;
        document.getElementById("cat-image").src = stockUrls.getCatImage(item.image); 
        document.getElementById("cat-text").innerHTML = item.text;
        document.getElementById("cat-price").innerHTML = `$${item.price}.00`;
        document.getElementById("cat-text-decoration-line-through-price").innerHTML =
            item.oldPrice ? `$${item.oldPrice}.00` : '';
        listener();
    }

    render(listener) {
        this.parent.innerHTML = this.getHTML();
        this.getData(listener);
    }


    getHTML(){
        return (`
            <head>
                <meta charset="utf-8" />
                <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
                <meta name="description" content="" />
                <meta name="author" content="" />
                <title>Shop Item - Start Bootstrap Template</title>
                <!-- Favicon-->
                <link rel="icon" type="image/x-icon" href="assets/favicon.ico" />
                <!-- Bootstrap icons-->
                <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.5.0/font/bootstrap-icons.css" rel="stylesheet" />
                <!-- Core theme CSS (includes Bootstrap)-->
                <link href="css/styles_page.css" rel="stylesheet" />
            </head>
            <body>
                <!-- Navigation-->
                    <nav class="navbar navbar-expand-lg navbar-light bg-light">
                        <div class="container px-4 px-lg-5">
                            <a class="navbar-brand">Кошкомаркет</a>
                            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation"><span class="navbar-toggler-icon"></span></button>
                            <div class="collapse navbar-collapse" id="navbarSupportedContent">
                                <ul class="navbar-nav me-auto mb-2 mb-lg-0 ms-lg-4">
                                    <li class="nav-item"><a class="nav-link active" aria-current="page" id="main">Главная</a></li>
                                </ul>
                            </div>
                        </div>
                    </nav>
                    <!-- Product section-->
                   <section class="py-5">
                    <div class="container px-4 px-lg-5 my-5">
                        <div class="row gx-4 gx-lg-5 align-items-center">
                            <div class="col-md-6">
                                <img id="cat-image" class="img-fluid rounded" style="max-width: 100%; height: auto;" src="" alt="Cat Image"/>
                            </div>
                            <div class="col-md-6">
                                <h1 id="cat-name" class="display-5 fw-bolder"></h1>
                                <div class="fs-5 mb-5">
                                    <span id="cat-text-decoration-line-through-price" class="text-muted text-decoration-line-through me-2"></span>
                                    <span id="cat-price"></span>
                                </div>
                                <p id="cat-text" class="lead"></p>
                                <div class="d-flex">
                                    <a id="back">
                                        <button class="btn btn-outline-dark flex-shrink-0" type="button">Назад</button>
                                    </a>
                                </div>
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
            </body>
            `)
    }

}