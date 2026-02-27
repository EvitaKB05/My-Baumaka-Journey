import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";
import { OrderModalComponent } from "../../components/order_modal/index.js";
import { ProductPage } from "../product/index.js";

export class CartPage {
    constructor(parent) {
        this.parent = parent;
        this.cartItems = JSON.parse(localStorage.getItem('cart')) || [];
    }

    get pageRoot() {
        return document.getElementById('cart-page');
    }

    getHTML() {
        return `
            <div id="cart-page">
                <div id="back-button-container"></div>
                <div id="order-modal-container"></div>
                <h2 class="mb-4 text-center">Моя корзина</h2>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="cart-items-container">
                    ${this.cartItems.length === 0 ? '<p class="text-center w-100">Корзина пуста</p>' : ''}
                </div>
            </div>
        `;
    }

    clickBack() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    handleRemoveFromCart(productId) {
        this.cartItems = this.cartItems.filter(id => id !== productId);
        localStorage.setItem('cart', JSON.stringify(this.cartItems));
        alert('Товар удален из корзины');
        this.render();
    }

    handleShowDetails(productId) {
        const productPage = new ProductPage(this.parent, productId);
        productPage.render();
    }

    renderProductCard(item) {
        return `
            <div class="card" style="width: 300px;">
                <img src="${item.src}" 
                     class="card-img-top" 
                     alt="${item.title}"
                     style="height: 200px; object-fit: cover;"
                     onerror="this.src='static/images/hamster.jpg'">
                <div class="card-body">
                    <h5 class="card-title">${item.title}</h5>
                    <p class="card-text">${item.text}</p>
                    <div class="d-flex flex-column gap-2 mt-3">
                        <button class="btn btn-outline-primary" id="details-${item.id}">
                            <i class="bi bi-info-circle"></i> Подробнее
                        </button>
                        <button class="btn btn-danger" id="remove-${item.id}">
                            <i class="bi bi-trash"></i> Удалить
                        </button>
                    </div>
                </div>
            </div>
        `;
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        // Инициализация модального окна заказа
        new OrderModalComponent(document.getElementById('order-modal-container')).render();

        // Кнопка назад
        new BackButtonComponent(document.getElementById('back-button-container'))
            .render(this.clickBack.bind(this));

        if (this.cartItems.length > 0) {
            const mainPage = new MainPage(this.parent);
            const data = mainPage.getData().filter(item => 
                this.cartItems.includes(item.id)
            );

            const cartContainer = document.getElementById('cart-items-container');
            data.forEach((item) => {
                cartContainer.insertAdjacentHTML('beforeend', this.renderProductCard(item));

                // Обработчики кнопок
                document.getElementById(`details-${item.id}`)
                    .addEventListener('click', () => this.handleShowDetails(item.id));
                
                document.getElementById(`remove-${item.id}`)
                    .addEventListener('click', () => this.handleRemoveFromCart(item.id));
            });
        }

        // Закрытие модальных окон по пробелу
        document.addEventListener('keydown', (e) => {
            if (e.code === 'Space') {
                const orderModal = bootstrap.Modal.getInstance(document.getElementById('orderModal'));
                if (orderModal) orderModal.hide();
            }
        });
    }
}