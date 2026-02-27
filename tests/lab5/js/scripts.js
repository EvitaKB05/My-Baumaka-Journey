import data from "../assets/data.json" with { type: "json" }

console.log(data.cats.length)
for(let i = 0; i < data.cats.length; i++)
{
    document.getElementById(i+1).addEventListener("click",loadData.bind(null,i+1))
}

function loadData(id, button){
    console.log(id)
    for(let i = 0; i < data.cats.length; i++)
    {
        if(data.cats[i].id == id)
        {
            console.log(data.cats[i].name)
            globalThis.cat_id = i
            break;
        }
    }
    document.getElementById('mainbody').innerHTML = getPageHTML()
    document.getElementById("cat-name").innerHTML = data.cats[globalThis.cat_id].name
    document.getElementById("cat-image").src = `assets/Cats/${data.cats[globalThis.cat_id].image}.jpg`
    document.getElementById("cat-text").innerHTML = data.cats[globalThis.cat_id].text
    document.getElementById('mainbody').insertAdjacentHTML('beforeend',getAlert(data.cats[globalThis.cat_id].name))
    setTimeout(()=>{document.getElementById('alert').style.display = 'none';},'1500')
}

function getPageHTML(){
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
                            <a class="navbar-brand" href="#!">Кошкомаркет</a>
                            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation"><span class="navbar-toggler-icon"></span></button>
                            <div class="collapse navbar-collapse" id="navbarSupportedContent">
                                <ul class="navbar-nav me-auto mb-2 mb-lg-0 ms-lg-4">
                                    <li class="nav-item"><a class="nav-link active" aria-current="page" href="index.html">Главная</a></li>
                                </ul>
                            </div>
                        </div>
                    </nav>
                    <!-- Product section-->
                    <section class="py-5">
                        <div class="container px-4 px-lg-5 my-5">
                            <div class="row gx-4 gx-lg-5 align-items-center">
                                <div class="col-md-6"><img class="card-img-top mb-5 mb-md-0" id="cat-image" src="https://dummyimage.com/600x700/dee2e6/6c757d.jpg" alt="..." /></div>
                                <div class="col-md-6">
                                    <div class="small mb-1">SKU: BST-498</div>
                                    <h1 id="cat-name" class="display-5 fw-bolder"></h1>
                                    <div class="fs-5 mb-5">
                                        <span id="cat-text-decoration-line-through-price" class="text-decoration-line-through">$45.00</span>
                                        <span id="cat-price">$40.00</span>
                                    </div>
                                    <p id="cat-text" class="lead">Lorem ipsum dolor sit amet consectetur adipisicing elit. Praesentium at dolorem quidem modi. Nam sequi consequatur obcaecati excepturi alias magni, accusamus eius blanditiis delectus ipsam minima ea iste laborum vero?</p>
                                    <div class="d-flex">
                                    <a href="index.html">
                                        <button class="btn btn-outline-dark flex-shrink-0" type="button">
                                            Назад
                                        </button>
                                    </a>
                                    </div>
                                </div>
                            </div>+
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

function getAlert(name){
    return(`
        <div id="alert" class="alert alert-primary" style="width:50%; margin:auto; margin-top:25px" role="alert">
        Отлично! Вы выбрали кошечку ${name}
        `)
}