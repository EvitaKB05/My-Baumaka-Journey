import { ProductCardComponent } from "../../components/product_card/index.js";
import { ProductPage } from "../product/index.js";
import { CategoryPage } from "../category/index.js";
import { CategoryCardComponent } from "../../components/category_card/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { AuthModalComponent } from "../../components/auth_modal/index.js";
import { CartPage } from "../cart/index.js";
import { OrderModalComponent } from "../../components/order_modal/index.js";
import { CreateStockPage } from "../create_stock/index.js";
import { ajax } from "../../modules/ajax.js";
import { stockUrls } from "../../modules/stockUrls.js";

/**
 * Главная страница приложения
 */
export class MainPage {
    constructor(parent) {
        this.parent = parent;
        this.showCategories = true;
        this.cart = JSON.parse(localStorage.getItem('cart')) || [];
    }

    get pageRoot() {
        return document.getElementById('main-page');
    }

    getHTML() {
        return `
            <div id="main-page">
                <nav class="navbar navbar-expand-lg bg-light mb-4">
                    <div class="container-fluid">
                        <form class="d-flex me-auto" role="search">
                            <input class="form-control me-2" type="search" placeholder="Поиск..." id="searchInput">
                        </form>
                        
                        <h1 class="navbar-brand mx-auto">Продуктовый магазин</h1>
                        
                        <div class="d-flex">
                            <button class="btn btn-success me-3" id="create-stock-button">
                                <i class="bi bi-plus"></i> Добавить продукт
                            </button>
                            <button class="btn btn-outline-success position-relative me-3" id="cartButton">
                                <i class="bi bi-cart"></i> Корзина
                                ${this.cart.length > 0 ? `
                                    <span class="position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger">
                                        ${this.cart.length}
                                    </span>
                                ` : ''}
                            </button>
                            <button class="btn btn-primary" id="authButton">
                                <i class="bi bi-person"></i> Войти
                            </button>
                        </div>
                    </div>
                </nav>
                
                <div id="back-button-container" style="display: none;"></div>
                <div id="auth-modal-container"></div>
                <div id="order-modal-container"></div>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="content-container"></div>
            </div>
        `;
    }

    getCategories() {
        return ['Мясо', 'Овощи', 'Фрукты', 'Молочные Продукты'];
    }

    // Изменено: теперь данные получаем через API
    getData() {
        ajax.get(stockUrls.getStocks(), (data) => {
            this.renderData(data);
        });
    }

    // Новый метод: отрисовка данных, полученных из API
    renderData(items) {
        const contentContainer = document.getElementById('content-container');
        contentContainer.innerHTML = '';
        
        items.forEach((item) => {
            const productCard = new ProductCardComponent(contentContainer);
            productCard.render(item, (id) => this.clickCard(id));
        });
    }

    handleCategoryClick = (category) => {
        this.showCategories = false;
        const categoryPage = new CategoryPage(this.parent, category);
        categoryPage.render();
    }

    clickCard(productId) {
        const productPage = new ProductPage(this.parent, productId);
        productPage.render();
    }

    handleAddToCart(productId) {
        if (!this.cart.includes(productId)) {
            this.cart.push(productId);
            localStorage.setItem('cart', JSON.stringify(this.cart));
            this.updateCartCounter();
            alert('Товар добавлен в корзину!');
        } else {
            alert('Этот товар уже в корзине');
        }
    }

    handleCartClick = () => {
        const cartPage = new CartPage(this.parent);
        cartPage.render();
    }

    handleAuthClick = () => {
        new bootstrap.Modal(document.getElementById('authModal')).show();
    }

    handleCreateStockClick = () => {
        const createPage = new CreateStockPage(this.parent);
        createPage.render();
    }

    clickBack() {
        this.showCategories = true;
        this.render();
    }

    updateCartCounter() {
        const cartButton = document.getElementById('cartButton');
        let counter = cartButton.querySelector('.badge');
        
        if (this.cart.length > 0) {
            if (!counter) {
                cartButton.insertAdjacentHTML('beforeend', `
                    <span class="position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger">
                        ${this.cart.length}
                    </span>
                `);
            } else {
                counter.textContent = this.cart.length;
            }
        } else if (counter) {
            counter.remove();
        }
    }

    initEventListeners() {
        document.getElementById('cartButton').addEventListener('click', this.handleCartClick);
        document.getElementById('authButton').addEventListener('click', this.handleAuthClick);
        document.getElementById('create-stock-button').addEventListener('click', this.handleCreateStockClick);

        document.addEventListener('keydown', (e) => {
            if (e.code === 'Space') {
                const authModal = bootstrap.Modal.getInstance(document.getElementById('authModal'));
                const orderModal = bootstrap.Modal.getInstance(document.getElementById('orderModal'));
                if (authModal) authModal.hide();
                if (orderModal) orderModal.hide();
            }
        });
    }

    renderContent() {
        const contentContainer = document.getElementById('content-container');
        const backButtonContainer = document.getElementById('back-button-container');

        if (this.showCategories) {
            backButtonContainer.style.display = 'none';
            const categories = this.getCategories();
            contentContainer.innerHTML = '';
            categories.forEach(category => {
                const categoryCard = new CategoryCardComponent(contentContainer);
                categoryCard.render(category, this.handleCategoryClick);
            });
        } else {
            backButtonContainer.style.display = 'block';
            const backButton = new BackButtonComponent(backButtonContainer);
            backButton.render(this.clickBack.bind(this));

            // Изменено: теперь данные получаем через API
            this.getData();
        }
    }

    render() {
        this.parent.innerHTML = '';
        this.parent.insertAdjacentHTML('beforeend', this.getHTML());

        new AuthModalComponent(document.getElementById('auth-modal-container')).render();
        new OrderModalComponent(document.getElementById('order-modal-container')).render();

        this.initEventListeners();
        this.renderContent();
    }
}