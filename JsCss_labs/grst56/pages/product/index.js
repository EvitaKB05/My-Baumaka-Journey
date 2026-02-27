import { ProductComponent } from "../../components/product/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { OrderModalComponent } from "../../components/order_modal/index.js";
import { MainPage } from "../main/index.js";
import { CartPage } from "../cart/index.js";
import { ajax } from "../../modules/ajax.js";
import { stockUrls } from "../../modules/stockUrls.js";

/**
 * Страница детального просмотра товара
 */
export class ProductPage {
    constructor(parent, id) {
        this.parent = parent;
        this.id = id;
        this.fromCart = false;
    }

    // Изменено: теперь данные получаем через API
    getData() {
        ajax.get(stockUrls.getStockById(this.id), (data) => {
            this.renderData(data);
        });
    }

    // Новый метод: отрисовка данных, полученных из API
    renderData(item) {
        const productContainer = document.getElementById('product-container');
        const product = new ProductComponent(productContainer);
        product.render(item);
    }

    get pageRoot() {
        return document.getElementById('product-page');
    }

    getHTML() {
        return `
            <div id="product-page">
                <div id="back-button-container"></div>
                <div id="order-modal-container"></div>
                <div id="product-container" class="mb-4"></div>
                <div class="d-flex gap-3">
                    <button class="btn btn-outline-secondary flex-grow-1 py-2" id="back-btn">
                        <i class="bi bi-arrow-left"></i> ${this.fromCart ? 'В корзину' : 'Назад'}
                    </button>
                    ${this.fromCart ? '' : `
                    <button class="btn btn-outline-primary flex-grow-1 py-2" id="add-to-cart">
                        <i class="bi bi-cart-plus"></i> В корзину
                    </button>
                    `}
                    <button class="btn btn-primary flex-grow-1 py-2" id="order-now">
                        <i class="bi bi-bag-check"></i> Заказать
                    </button>
                </div>
            </div>
        `;
    }

    clickBack() {
        if (this.fromCart) {
            const cartPage = new CartPage(this.parent);
            cartPage.render();
        } else {
            const mainPage = new MainPage(this.parent);
            mainPage.render();
        }
    }

    handleAddToCart() {
        const mainPage = new MainPage(this.parent);
        mainPage.handleAddToCart(this.id);
        alert('Товар добавлен в корзину!');
    }

    handleOrder() {
        new bootstrap.Modal(document.getElementById('orderModal')).show();
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        // Инициализация модального окна
        new OrderModalComponent(document.getElementById('order-modal-container')).render();

        // Кнопка назад
        new BackButtonComponent(document.getElementById('back-button-container'))
            .render(this.clickBack.bind(this));

        // Изменено: теперь данные получаем через API
        this.getData();

        // Обработчики кнопок
        document.getElementById('add-to-cart')?.addEventListener('click', () => {
            const mainPage = new MainPage(this.parent);
            mainPage.handleAddToCart(this.id);
        });

        document.getElementById('order-now').addEventListener('click', () => {
            new bootstrap.Modal(document.getElementById('orderModal')).show();
        });
    }
}