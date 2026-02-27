var f=Object.defineProperty;var y=(s,t,e)=>t in s?f(s,t,{enumerable:!0,configurable:!0,writable:!0,value:e}):s[t]=e;var g=(s,t,e)=>y(s,typeof t!="symbol"?t+"":t,e);(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const r of document.querySelectorAll('link[rel="modulepreload"]'))a(r);new MutationObserver(r=>{for(const i of r)if(i.type==="childList")for(const o of i.addedNodes)o.tagName==="LINK"&&o.rel==="modulepreload"&&a(o)}).observe(document,{childList:!0,subtree:!0});function e(r){const i={};return r.integrity&&(i.integrity=r.integrity),r.referrerPolicy&&(i.referrerPolicy=r.referrerPolicy),r.crossOrigin==="use-credentials"?i.credentials="include":r.crossOrigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function a(r){if(r.ep)return;r.ep=!0;const i=e(r);fetch(r.href,i)}})();class v{constructor(t){this.parent=t}getHTML(t){return`
              <span class="badge ${{Мясо:"bg-danger",Овощи:"bg-success",Фрукты:"bg-warning","Молочные Продукты":"bg-info",Грибы:"bg-secondary"}[t]}">${t}</span>
          `}render(t){const e=this.getHTML(t);this.parent.insertAdjacentHTML("beforeend",e)}}class d{constructor(t){this.parent=t}addListeners(t){document.getElementById("back-button").addEventListener("click",t)}getHTML(){return`
              <button id="back-button" style = "margin-bottom: 10px;" class="btn btn-primary" type="button">Назад</button>
          `}render(t){const e=this.getHTML();this.parent.insertAdjacentHTML("beforeend",e),this.addListeners(t)}}class x{constructor(t,e){this.parent=t,this.productId=e,this.product=null,this.categories=[]}getHTML(){return this.product?`
            <div id="edit-page">
                <div id="back-button-container"></div>
                <h2 class="text-center mb-4">Редактировать продукт</h2>
                <form id="edit-form" class="mx-auto" style="max-width: 500px;">
                    <div class="mb-3">
                        <label for="title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="title" 
                               value="${this.product.title}" required>
                    </div>
                    <div class="mb-3">
                        <label for="description" class="form-label">Описание</label>
                        <textarea class="form-control" id="description" rows="3" required>${this.product.text}</textarea>
                    </div>
                    <div class="mb-3">
                        <label for="price" class="form-label">Цена</label>
                        <input type="number" class="form-control" id="price" 
                               value="${this.product.price||""}" required>
                    </div>
                    <div class="mb-3">
                        <label for="category" class="form-label">Категория</label>
                        <select class="form-select" id="category" required>
                            ${this.categories.map(t=>`<option value="${t.id}" ${t.title===this.product.category?"selected":""}>
                                    ${t.title}
                                </option>`).join("")}
                        </select>
                    </div>
                    <div class="mb-3">
                        <label for="imageUrl" class="form-label">URL изображения</label>
                        <input type="url" class="form-control" id="imageUrl" 
                               value="${this.product.src}" 
                               placeholder="Оставьте пустым для изображения по умолчанию">
                    </div>
                    <div class="d-flex gap-2">
                        <button type="submit" class="btn btn-primary flex-grow-1">Сохранить</button>
                        <button type="button" id="delete-btn" class="btn btn-danger">Удалить</button>
                    </div>
                </form>
            </div>
        `:"<div>Загрузка...</div>"}getData(){return new n(this.parent).getData()}findProduct(){const t=this.getData();for(const e of t){const a=e.products.find(r=>r.id===this.productId);if(a)return a.category_id=e.id,a}return null}handleSubmit(t){t.preventDefault();const e=document.getElementById("title").value,a=document.getElementById("description").value,r=parseFloat(document.getElementById("price").value),i=document.getElementById("category").selectedOptions[0].text;let o=document.getElementById("imageUrl").value;o||(o="static/images/hamster.jpg"),this.product.title=e,this.product.text=a,this.product.price=r,this.product.src=o,this.product.category=i,alert("Продукт успешно обновлен!"),new n(this.parent).render()}handleDelete(){if(confirm("Вы уверены, что хотите удалить этот продукт?")){const t=this.getData();for(const a of t){const r=a.products.findIndex(i=>i.id===this.productId);if(r!==-1){a.products.splice(r,1);break}}alert("Продукт успешно удален!"),new n(this.parent).render()}}async render(){const t=this.getData();if(this.categories=t.map(a=>({id:a.id,title:a.title})),this.product=this.findProduct(),!this.product){alert("Продукт не найден"),new n(this.parent).render();return}this.parent.innerHTML="",this.parent.insertAdjacentHTML("beforeend",this.getHTML()),new d(document.getElementById("back-button-container")).render(()=>{new n(this.parent).render()}),document.getElementById("edit-form").addEventListener("submit",a=>this.handleSubmit(a)),document.getElementById("delete-btn").addEventListener("click",()=>this.handleDelete())}}class u{constructor(t){this.parent=t}getProductImage(t){return t.src&&t.src.startsWith("static/images/")?t.src:`static/images/${{Говядина:"beef.jpg",Баранина:"lamb.jpg",Курица:"chicken.jpg",Морковь:"carrots.jpg",Твинк:"twink.jpg",Помидоры:"tomatoes.jpg",Апельсины:"oranges.jpg",Бананы:"bananas.jpg",Яблоки:"apples.jpg",Молоко:"milk.jpg",Сыр:"cheese.jpg","Сливочное масло":"butter.jpg"}[t.title]||"hamster.jpg"}`}getHTML(t){return`
        <div class="card" style="width: 300px; margin: 10px;">
            <img src="${this.getProductImage(t)}" 
                 class="card-img-top" 
                 alt="${t.title}"
                 style="height: 200px; object-fit: cover;"
                 onerror="this.src='static/images/hamster.jpg'">
            <div class="card-body">
                <h5 class="card-title">${t.title}</h5>
                <div id="badge-${t.id}"></div>
                <p class="card-text">${t.text}</p>
                ${t.price?`<p class="card-text"><strong>Цена:</strong> ${t.price} руб.</p>`:""}
                <div class="d-flex gap-2">
                    <button class="btn btn-primary flex-grow-1" id="details-${t.id}">Подробнее</button>
                    <button class="btn btn-outline-secondary" id="edit-${t.id}">
                        <i class="bi bi-pencil"></i>
                    </button>
                </div>
            </div>
        </div>
    `}addListeners(t,e){document.getElementById(`details-${t.id}`).addEventListener("click",()=>e(t.id)),document.getElementById(`edit-${t.id}`).addEventListener("click",()=>{new x(this.parent.parentElement,t.id).render()})}render(t,e){const a=this.getHTML(t);this.parent.insertAdjacentHTML("beforeend",a),this.addListeners(t,e);const r=document.getElementById(`badge-${t.id}`);new v(r).render(t.category)}}class I{constructor(t){this.parent=t}getHTML(t){return`
                <div class="card mb-3" style="width: 540px;">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${t.src||"static/images/hamster.jpg"}" 
                                 class="img-fluid" 
                                 alt="${t.title||"Изображение продукта"}"
                                 style="height: 100%; object-fit: cover;"
                                 onerror="this.src='static/images/hamster.jpg'">
                        </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">${t.title}</h5>
                                <p class="card-text">${t.text}</p>
                            </div>
                        </div>
                    </div>
                </div>
            `}render(t){const e=this.getHTML(t);this.parent.insertAdjacentHTML("beforeend",e)}}class m{constructor(t){this.parent=t}getHTML(){return`
            <div class="modal fade" id="orderModal" tabindex="-1" aria-hidden="true">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title">Оформление заказа</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div class="modal-body">
                            <form id="orderForm">
                                <div class="mb-3">
                                    <label for="address" class="form-label">Адрес доставки</label>
                                    <input type="text" class="form-control" id="address" required>
                                </div>
                                <div class="mb-3">
                                    <label for="time" class="form-label">Время доставки</label>
                                    <select class="form-select" id="time" required>
                                        <option value="">Выберите время</option>
                                        <option value="6:00-9:00">С 6:00 до 9:00</option>
                                        <option value="10:00-12:00">С 10:00 до 12:00</option>
                                        <option value="12:00-14:00">С 12:00 до 14:00</option>
                                        <option value="14:00-17:00">С 14:00 до 17:00</option>
                                        <option value="17:00-21:00">С 17:00 до 21:00</option>
                                    </select>
                                </div>
                            </form>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отмена</button>
                            <button type="submit" form="orderForm" class="btn btn-primary">Оформить</button>
                        </div>
                    </div>
                </div>
            </div>
        `}render(){const t=this.getHTML();this.parent.insertAdjacentHTML("beforeend",t),document.getElementById("orderForm").addEventListener("submit",e=>{e.preventDefault(),bootstrap.Modal.getInstance(document.getElementById("orderModal")).hide(),alert("Вы успешно заказали продукт!")})}}class p{constructor(t,e){this.parent=t,this.id=e}getData(){return[{id:1,src:"static/images/beef.jpg",title:"Говядина",text:"Свежая говядина высшего качества. Идеально подходит для стейков и гуляша.",category:"Мясо",price:"500 руб/кг"},{id:2,src:"static/images/lamb.jpg",title:"Баранина",text:"Нежная баранина. Отлично подходит для плова и шашлыка.",category:"Мясо",price:"600 руб/кг"},{id:3,src:"static/images/chicken.jpg",title:"Курица",text:"Куриные грудки. Диетический продукт с высоким содержанием белка.",category:"Мясо",price:"300 руб/кг"},{id:4,src:"static/images/carrots.jpg",title:"Морковь",text:"Свежая морковь. Богата витамином А и клетчаткой.",category:"Овощи",price:"50 руб/кг"},{id:5,src:"static/images/twink.jpg",title:"Главный овощ",text:"Rust'ер и этим всё сказано, никогда не трезв, любит пиво и носить чулки",category:"Овощи",price:"50 руб/кг (торг уместен)"},{id:6,src:"static/images/tomatoes.jpg",title:"Помидоры",text:"Сочные помидоры. Содержат ликопин - мощный антиоксидант.",category:"Овощи",price:"150 руб/кг"},{id:7,src:"static/images/oranges.jpg",title:"Апельсины",text:"Сладкие апельсины. Богаты витамином С.",category:"Фрукты",price:"120 руб/кг"},{id:8,src:"static/images/bananas.jpg",title:"Бананы",text:"Спелые бананы. Отличный источник калия и энергии.",category:"Фрукты",price:"80 руб/кг"},{id:9,src:"static/images/apples.jpg",title:"Яблоки",text:"Красные яблоки. Содержат пектин и множество витаминов.",category:"Фрукты",price:"90 руб/кг"},{id:10,src:"static/images/milk.jpg",title:"Молоко 3,2 %",text:"Полезный и природный продукт.",category:"Молочные Продукты",price:"100 руб/л"},{id:11,src:"static/images/cheese.jpg",title:"Сыр классический",text:"Любимец мышек и британцев.",category:"Молочные Продукты",price:"200 руб/100 г"},{id:12,src:"static/images/butter.jpg",title:"Сливочное масло 5 %",text:"Очень нужный товарищ для вкусняшек.",category:"Молочные Продукты",price:"250 руб/100 г"}].find(e=>e.id===parseInt(this.id))}get pageRoot(){return document.getElementById("product-page")}getHTML(){return`
        <div id="product-page">
            <div id="back-button-container"></div>
            <div id="order-modal-container"></div>
            <div id="product-container" class="mb-4"></div>
            <div class="d-flex gap-3">
                <button class="btn btn-outline-secondary flex-grow-1 py-2" id="back-btn">
                    <i class="bi bi-arrow-left"></i> ${this.fromCart?"В корзину":"Назад"}
                </button>
                ${this.fromCart?"":`
                <button class="btn btn-outline-primary flex-grow-1 py-2" id="add-to-cart">
                    <i class="bi bi-cart-plus"></i> В корзину
                </button>
                `}
                <button class="btn btn-outline-warning flex-grow-1 py-2" id="edit-btn">
                    <i class="bi bi-pencil"></i> Редактировать
                </button>
                <button class="btn btn-primary flex-grow-1 py-2" id="order-now">
                    <i class="bi bi-bag-check"></i> Заказать
                </button>
            </div>
        </div>
    `}clickBack(){this.fromCart?new CartPage(this.parent).render():new n(this.parent).render()}handleAddToCart(){new n(this.parent).handleAddToCart(this.id),alert("Товар добавлен в корзину!")}handleOrder(){new bootstrap.Modal(document.getElementById("orderModal")).show()}render(){this.parent.innerHTML="";const t=this.getHTML();this.parent.insertAdjacentHTML("beforeend",t),new m(document.getElementById("order-modal-container")).render(),new d(document.getElementById("back-button-container")).render(()=>{new n(this.parent).render()});const e=this.getData();new I(document.getElementById("product-container")).render(e),document.getElementById("add-to-cart").addEventListener("click",()=>{new n(this.parent).handleAddToCart(this.id)}),document.getElementById("order-now").addEventListener("click",()=>{new bootstrap.Modal(document.getElementById("orderModal")).show()})}}class w{constructor(t,e,a){this.parent=t,this.category=e,this.mainPage=a}get pageRoot(){return document.getElementById("category-page")}getHTML(){return`
            <div id="category-page">
                <div id="back-button-container"></div>
                <h2 class="mb-4 text-center">${this.category}</h2>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="products-container"></div>
            </div>
        `}clickBack(){this.mainPage.showCategories=!0,this.mainPage.render()}render(){this.parent.innerHTML="",this.parent.insertAdjacentHTML("beforeend",this.getHTML());const t=document.getElementById("back-button-container");new d(t).render(this.clickBack.bind(this));const a=this.mainPage.getData().find(i=>i.title===this.category);if(!a||!a.products){console.error(`Данные для категории "${this.category}" не найдены`);return}const r=document.getElementById("products-container");a.products.forEach(i=>{new u(r).render(i,c=>this.mainPage.clickCard(c),c=>this.mainPage.handleAddToCart(c))})}}class E{constructor(t){this.parent=t}render(t,e){if(!t||typeof t!="object"){console.error("Invalid category data received:",t);return}const a=document.createElement("div");a.className="card",a.style.width="300px",a.style.cursor="pointer",a.style.margin="15px",a.style.boxShadow="0 4px 8px rgba(0,0,0,0.1)";const r=t.src||"/static/images/default_category.jpg",i=t.title||"Категория товаров";a.innerHTML=`
            <img src="${r}" 
                 class="card-img-top" 
                 alt="${i}"
                 style="height: 200px; object-fit: cover;"
                 onerror="this.src='/static/images/default_category.jpg';">
            <div class="card-body">
                <h5 class="card-title text-center">${t.title||"Категория"}</h5>
            </div>
        `,a.addEventListener("click",()=>{typeof e=="function"&&e()}),this.parent.appendChild(a)}}class B{constructor(t){this.parent=t}getHTML(){return`
            <div class="modal fade" id="authModal" tabindex="-1" aria-hidden="true">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title">Вход / Регистрация</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div class="modal-body">
                            <form id="authForm">
                                <div class="mb-3">
                                    <label for="email" class="form-label">Email</label>
                                    <input type="email" class="form-control" id="email" required>
                                </div>
                                <div class="mb-3">
                                    <label for="password" class="form-label">Пароль</label>
                                    <input type="password" class="form-control" id="password" required>
                                </div>
                            </form>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отмена</button>
                            <button type="submit" form="authForm" class="btn btn-primary">Войти</button>
                        </div>
                    </div>
                </div>
            </div>
        `}render(){const t=this.getHTML();this.parent.insertAdjacentHTML("beforeend",t),document.getElementById("authForm").addEventListener("submit",e=>{e.preventDefault(),alert("Вы успешно авторизованы!"),bootstrap.Modal.getInstance(document.getElementById("authModal")).hide()})}}let C=class{constructor(t){this.parent=t,this.cartItems=JSON.parse(localStorage.getItem("cart"))||[]}get pageRoot(){return document.getElementById("cart-page")}getHTML(){return`
            <div id="cart-page">
                <div id="back-button-container"></div>
                <div id="order-modal-container"></div>
                <h2 class="mb-4 text-center">Моя корзина</h2>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="cart-items-container">
                    ${this.cartItems.length===0?'<p class="text-center w-100">Корзина пуста</p>':""}
                </div>
            </div>
        `}clickBack(){new n(this.parent).render()}handleRemoveFromCart(t){this.cartItems=this.cartItems.filter(e=>e!==t),localStorage.setItem("cart",JSON.stringify(this.cartItems)),alert("Товар удален из корзины"),this.render()}handleShowDetails(t){new p(this.parent,t).render()}renderProductCard(t){return`
            <div class="card" style="width: 300px;">
                <img src="${t.src}" 
                     class="card-img-top" 
                     alt="${t.title}"
                     style="height: 200px; object-fit: cover;"
                     onerror="this.src='static/images/hamster.jpg'">
                <div class="card-body">
                    <h5 class="card-title">${t.title}</h5>
                    <p class="card-text">${t.text}</p>
                    <div class="d-flex flex-column gap-2 mt-3">
                        <button class="btn btn-outline-primary" id="details-${t.id}">
                            <i class="bi bi-info-circle"></i> Подробнее
                        </button>
                        <button class="btn btn-danger" id="remove-${t.id}">
                            <i class="bi bi-trash"></i> Удалить
                        </button>
                    </div>
                </div>
            </div>
        `}render(){this.parent.innerHTML="";const t=this.getHTML();if(this.parent.insertAdjacentHTML("beforeend",t),new m(document.getElementById("order-modal-container")).render(),new d(document.getElementById("back-button-container")).render(this.clickBack.bind(this)),this.cartItems.length>0){const a=new n(this.parent).getData().filter(i=>this.cartItems.includes(i.id)),r=document.getElementById("cart-items-container");a.forEach(i=>{r.insertAdjacentHTML("beforeend",this.renderProductCard(i)),document.getElementById(`details-${i.id}`).addEventListener("click",()=>this.handleShowDetails(i.id)),document.getElementById(`remove-${i.id}`).addEventListener("click",()=>this.handleRemoveFromCart(i.id))})}document.addEventListener("keydown",e=>{if(e.code==="Space"){const a=bootstrap.Modal.getInstance(document.getElementById("orderModal"));a&&a.hide()}})}};class L{constructor(t){this.parent=t,this.categories=[]}getHTML(){return`
            <div id="create-page">
                <div id="back-button-container"></div>
                <h2 class="text-center mb-4">Добавить новый продукт</h2>
                <form id="create-form" class="mx-auto" style="max-width: 500px;">
                    <div class="mb-3">
                        <label for="title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="title" required>
                    </div>
                    <div class="mb-3">
                        <label for="description" class="form-label">Описание</label>
                        <textarea class="form-control" id="description" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="price" class="form-label">Цена</label>
                        <input type="number" class="form-control" id="price" min="0" step="0.01" required>
                    </div>
                    <div class="mb-3">
                        <label for="category" class="form-label">Категория</label>
                        <select class="form-select" id="category" required>
                            <option value="" selected disabled>Выберите категорию</option>
                            ${this.categories.map(t=>`<option value="${t.id}">${t.title}</option>`).join("")}
                        </select>
                    </div>
                    <div class="mb-3">
                        <label for="imageUrl" class="form-label">URL изображения</label>
                        <input type="url" class="form-control" id="imageUrl" 
                               placeholder="Оставьте пустым для изображения по умолчанию">
                    </div>
                    <button type="submit" class="btn btn-primary w-100">Добавить продукт</button>
                </form>
            </div>
        `}getCategories(){const t=localStorage.getItem("storeData");return t?JSON.parse(t):new n(this.parent).getData()}saveCategories(t){localStorage.setItem("storeData",JSON.stringify(t))}generateUniqueId(t){const e=t.flatMap(r=>r.products);let a;do a=Math.floor(Math.random()*1e6);while(e.some(r=>r.id===a));return a}handleSubmit(t){t.preventDefault();const e=document.getElementById("title").value.trim(),a=document.getElementById("description").value.trim(),r=parseFloat(document.getElementById("price").value),i=parseInt(document.getElementById("category").value);let o=document.getElementById("imageUrl").value.trim();if(!e||!a||isNaN(r)||r<0||isNaN(i)){alert("Пожалуйста, заполните все обязательные поля корректно");return}o||(o="static/images/hamster.jpg");const c=this.getCategories(),l=c.find(b=>b.id===i);if(!l){alert("Ошибка: категория не найдена");return}const h={id:this.generateUniqueId(c),title:e,text:a,price:r,src:o,category:l.title};l.products.push(h),this.saveCategories(c),alert(`Продукт "${e}" успешно добавлен в категорию "${l.title}"!`),new n(this.parent).render()}async render(){const t=this.getCategories();this.categories=t.map(a=>({id:a.id,title:a.title})),this.parent.innerHTML="",this.parent.insertAdjacentHTML("beforeend",this.getHTML()),new d(document.getElementById("back-button-container")).render(()=>{new n(this.parent).render()}),document.getElementById("create-form").addEventListener("submit",a=>this.handleSubmit(a))}}class n{constructor(t){g(this,"handleCategoryClick",t=>{this.showCategories=!1,this.currentCategory=t,new w(this.parent,t,this).render()});g(this,"handleCartClick",()=>{new C(this.parent).render()});g(this,"handleAuthClick",()=>{new bootstrap.Modal(document.getElementById("authModal")).show()});this.parent=t,this.showCategories=!0,this.cart=JSON.parse(localStorage.getItem("cart"))||[],this.currentCategory=null,this.productsData=JSON.parse(localStorage.getItem("productsData"))||this.getDefaultData()}get pageRoot(){return document.getElementById("main-page")}getHTML(){return`
            <div id="main-page">
                <nav class="navbar navbar-expand-lg bg-light mb-4">
                    <div class="container-fluid">
                        <form class="d-flex me-auto" role="search">
                            <input class="form-control me-2" type="search" placeholder="Поиск..." id="searchInput">
                        </form>
                        
                        <h1 class="navbar-brand mx-auto">Продуктовый магазин</h1>
                        
                        <div class="d-flex">
                            <button class="btn btn-outline-success position-relative me-3" id="cartButton">
                                <i class="bi bi-cart"></i> Корзина
                                ${this.cart.length>0?`
                                    <span class="position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger">
                                        ${this.cart.length}
                                    </span>
                                `:""}
                            </button>
                            <button class="btn btn-primary" id="authButton">
                                <i class="bi bi-person"></i> Войти
                            </button>
                             <button class="btn btn-success ms-2" id="createButton">
                            <i class="bi bi-plus-circle"></i> Добавить
                            </button>
                        </div>
                    </div>
                </nav>
                
                <div id="back-button-container" style="display: none;"></div>
                <div id="auth-modal-container"></div>
                <div id="order-modal-container"></div>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="content-container"></div>
            </div>
        `}getDefaultData(){return[{id:1,title:"Мясо",src:"static/images/meat_category.jpg",products:[{id:1,src:"/static/images/beef.jpg",title:"Говядина",text:"Свежая говядина",category:"Мясо"},{id:2,src:"/static/images/lamb.jpg",title:"Баранина",text:"Нежная баранина",category:"Мясо"},{id:3,src:"/static/images/chicken.jpg",title:"Курица",text:"Куриные грудки",category:"Мясо"}]},{id:2,title:"Овощи",src:"static/images/vegetables_category.jpg",products:[{id:4,src:"/static/images/carrots.jpg",title:"Морковь",text:"Свежая морковь",category:"Овощи"},{id:5,src:"/static/images/twink.jpg",title:"Твинк",text:"Просто твинк",category:"Овощи"},{id:6,src:"/static/images/tomatoes.jpg",title:"Помидоры",text:"Сочные помидоры",category:"Овощи"}]},{id:3,title:"Фрукты",src:"static/images/fruits_category.jpg",products:[{id:7,src:"/static/images/oranges.jpg",title:"Апельсины",text:"Сладкие апельсины",category:"Фрукты"},{id:8,src:"/static/images/bananas.jpg",title:"Бананы",text:"Спелые бананы",category:"Фрукты"},{id:9,src:"/static/images/apples.jpg",title:"Яблоки",text:"Красные яблоки",category:"Фрукты"}]},{id:4,title:"Молочные Продукты",src:"static/images/dairy_category.jpg",products:[{id:10,src:"static/images/milk.jpg",title:"Молоко",text:"Молоко 3,2 %",category:"Молочные Продукты"},{id:11,src:"static/images/cheese.jpg",title:"Сыр",text:"Сыр классический",category:"Молочные Продукты"},{id:12,src:"static/images/butter.jpg",title:"Сливочное масло",text:"Сливочное масло 5 %",category:"Молочные Продукты"}]}]}getData(){const t=localStorage.getItem("storeData");return t?JSON.parse(t):this.getDefaultData()}saveData(){localStorage.setItem("productsData",JSON.stringify(this.productsData))}clickCard(t){new p(this.parent,t).render()}handleAddToCart(t){this.cart.includes(t)?alert("Этот товар уже в корзине"):(this.cart.push(t),localStorage.setItem("cart",JSON.stringify(this.cart)),alert("Товар добавлен в корзину!"))}clickBack(){this.showCategories=!0,this.currentCategory=null,this.render()}updateCartCounter(){const t=document.getElementById("cartButton");if(!t)return;let e=t.querySelector(".badge");this.cart.length>0?e?e.textContent=this.cart.length:t.insertAdjacentHTML("beforeend",`
                    <span class="position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger">
                        ${this.cart.length}
                    </span>
                `):e&&e.remove()}initEventListeners(){document.getElementById("cartButton").addEventListener("click",this.handleCartClick),document.getElementById("authButton").addEventListener("click",this.handleAuthClick),document.getElementById("createButton").addEventListener("click",()=>{new L(this.parent).render()}),document.addEventListener("keydown",t=>{if(t.code==="Space"){const e=bootstrap.Modal.getInstance(document.getElementById("authModal")),a=bootstrap.Modal.getInstance(document.getElementById("orderModal"));e&&e.hide(),a&&a.hide()}})}renderContent(){const t=document.getElementById("content-container"),e=document.getElementById("back-button-container");if(this.showCategories){e.style.display="none";const a=this.getData();t.innerHTML="",a.forEach(r=>{new E(t).render(r,()=>this.handleCategoryClick(r.title))})}else{e.style.display="block",new d(e).render(this.clickBack.bind(this));const r=this.getData().find(i=>i.title===this.currentCategory);t.innerHTML="",r&&r.products&&r.products.forEach(i=>{new u(t).render(i,c=>this.clickCard(c),c=>this.handleAddToCart(c))})}}render(){this.parent.innerHTML="",this.parent.insertAdjacentHTML("beforeend",this.getHTML()),new B(document.getElementById("auth-modal-container")).render(),new m(document.getElementById("order-modal-container")).render(),this.initEventListeners(),this.renderContent(),this.updateCartCounter()}}const M=document.getElementById("app"),j=new n(M);j.render();
