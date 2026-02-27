import { ProductCardComponent } from "../../components/product_card/index.js";
import { ProductPage } from "../product/index.js";
import { CategoryPage } from "../category/index.js";
import { CategoryCardComponent } from "../../components/category_card/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { AuthModalComponent } from "../../components/auth_modal/index.js";
import { CartPage } from "../cart/index.js";
import { OrderModalComponent } from "../../components/order_modal/index.js";

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

    getData() {
        return [
            {
                id: 1,
                src: "/static/images/beef.jpg",
                title: "Говядина",
                text: "Свежая говядина",
                category: "Мясо"
            },
            {
                id: 2,
                src: "/static/images/lamb.jpg",
                title: "Баранина",
                text: "Нежная баранина",
                category: "Мясо"
            },
            {
                id: 3,
                src: "/static/images/chicken.jpg",
                title: "Курица",
                text: "Куриные грудки",
                category: "Мясо"
            },
            {
                id: 4,
                src: "/static/images/carrots.jpg",
                title: "Морковь",
                text: "Свежая морковь",
                category: "Овощи"
            },
            {
                id: 5,
                src: "/static/images/twink.jpg",
                title: "Твинк",
                text: "Просто твинк",
                category: "Овощи"
            },
            {
                id: 6,
                src: "/static/images/tomatoes.jpg",
                title: "Помидоры",
                text: "Сочные помидоры",
                category: "Овощи"
            },
            {
                id: 7,
                src: "/static/images/oranges.jpg",
                title: "Апельсины",
                text: "Сладкие апельсины",
                category: "Фрукты"
            },
            {
                id: 8,
                src: "/static/images/bananas.jpg",
                title: "Бананы",
                text: "Спелые бананы",
                category: "Фрукты"
            },
            {
                id: 9,
                src: "/static/images/apples.jpg",
                title: "Яблоки",
                text: "Красные яблоки",
                category: "Фрукты"
            },
            {
                id: 10,
                src: "static/images/milk.jpg",
                title: "Молоко",
                text: "Молоко 3,2 %",
                category: "Молочные Продукты",
            },
            {
                id: 11,
                src: "static/images/cheese.jpg",
                title: "Сыр",
                text: "Сыр классический",
                category: "Молочные Продукты",
            },
            {
                id: 12,
                src: "static/images/butter.jpg",
                title: "Сливочное масло",
                text: "Сливочное масло 5 %",
                category: "Молочные Продукты",
            }
        ];
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

            const data = this.getData();
            contentContainer.innerHTML = '';
            data.forEach(item => {
                const productCard = new ProductCardComponent(contentContainer);
                productCard.render(item, (id) => this.clickCard(id));
            });
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