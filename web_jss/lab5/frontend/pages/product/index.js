import { ProductComponent } from "../../components/product/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { OrderModalComponent } from "../../components/order_modal/index.js";
import { MainPage } from "../main/index.js";

export class ProductPage {
    constructor(parent, id) {
        this.parent = parent;
        this.id = id;
    }


    getData() {
        const allProducts = [
            {
                id: 1,
                src: "static/images/beef.jpg",
                title: "Говядина",
                text: "Свежая говядина высшего качества. Идеально подходит для стейков и гуляша.",
                category: "Мясо",
                price: "500 руб/кг"
            },
            {
                id: 2,
                src: "static/images/lamb.jpg",
                title: "Баранина",
                text: "Нежная баранина. Отлично подходит для плова и шашлыка.",
                category: "Мясо",
                price: "600 руб/кг"
            },
            {
                id: 3,
                src: "static/images/chicken.jpg",
                title: "Курица",
                text: "Куриные грудки. Диетический продукт с высоким содержанием белка.",
                category: "Мясо",
                price: "300 руб/кг"
            },
            {
                id: 4,
                src: "static/images/carrots.jpg",
                title: "Морковь",
                text: "Свежая морковь. Богата витамином А и клетчаткой.",
                category: "Овощи",
                price: "50 руб/кг"
            },
            {
                id: 5,
                src: "static/images/twink.jpg",
                title: "Главный овощ",
                text: "Rust'ер и этим всё сказано, никогда не трезв, любит пиво и носить чулки",
                category: "Овощи",
                price: "50 руб/кг (торг уместен)"
            },
            {
                id: 6,
                src: "static/images/tomatoes.jpg",
                title: "Помидоры",
                text: "Сочные помидоры. Содержат ликопин - мощный антиоксидант.",
                category: "Овощи",
                price: "150 руб/кг"
            },
            {
                id: 7,
                src: "static/images/oranges.jpg",
                title: "Апельсины",
                text: "Сладкие апельсины. Богаты витамином С.",
                category: "Фрукты",
                price: "120 руб/кг"
            },
            {
                id: 8,
                src: "static/images/bananas.jpg",
                title: "Бананы",
                text: "Спелые бананы. Отличный источник калия и энергии.",
                category: "Фрукты",
                price: "80 руб/кг"
            },
            {
                id: 9,
                src: "static/images/apples.jpg",
                title: "Яблоки",
                text: "Красные яблоки. Содержат пектин и множество витаминов.",
                category: "Фрукты",
                price: "90 руб/кг"
            },
            {
                id: 10,
                src: "static/images/milk.jpg",
                title: "Молоко 3,2 %",
                text: "Полезный и природный продукт.",
                category: "Молочные Продукты",
                price: "100 руб/л"
            },
            {
                id: 11,
                src: "static/images/cheese.jpg",
                title: "Сыр классический",
                text: "Любимец мышек и британцев.",
                category: "Молочные Продукты",
                price: "200 руб/100 г"
            },
            {
                id: 12,
                src: "static/images/butter.jpg",
                title: "Сливочное масло 5 %",
                text: "Очень нужный товарищ для вкусняшек.",
                category: "Молочные Продукты",
                price: "250 руб/100 г"
            }
        ];

        return allProducts.find(item => item.id === parseInt(this.id));
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
            .render(() => {
                const mainPage = new MainPage(this.parent);
                mainPage.render();
            });

        // Данные продукта
        const data = this.getData();
        const product = new ProductComponent(document.getElementById('product-container'));
        product.render(data);

        // Обработчики кнопок
        document.getElementById('add-to-cart').addEventListener('click', () => {
            const mainPage = new MainPage(this.parent);
            mainPage.handleAddToCart(this.id);
        });

        document.getElementById('order-now').addEventListener('click', () => {
            new bootstrap.Modal(document.getElementById('orderModal')).show();
        });
    }
}