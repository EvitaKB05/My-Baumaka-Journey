import { ProductCardComponent } from "../../components/product_card/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";

export class CategoryPage {
    constructor(parent, category, mainPageInstance) {
        this.parent = parent;
        this.category = category;
        this.mainPage = mainPageInstance; // Сохраняем ссылку на главную страницу
    }

    get pageRoot() {
        return document.getElementById('category-page');
    }

    getHTML() {
        return `
            <div id="category-page">
                <div id="back-button-container"></div>
                <h2 class="mb-4 text-center">${this.category}</h2>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="products-container"></div>
            </div>
        `;
    }

    clickBack() {
        this.mainPage.showCategories = true;
        this.mainPage.render();
    }

    render() {
        this.parent.innerHTML = '';
        this.parent.insertAdjacentHTML('beforeend', this.getHTML());

        // Рендер кнопки "Назад"
        const backButtonContainer = document.getElementById('back-button-container');
        const backButton = new BackButtonComponent(backButtonContainer);
        backButton.render(this.clickBack.bind(this));

        // Получаем данные категории
        const categoryData = this.mainPage.getData().find(cat => cat.title === this.category);
        
        if (!categoryData || !categoryData.products) {
            console.error(`Данные для категории "${this.category}" не найдены`);
            return;
        }

        // Рендер продуктов категории
        const productsContainer = document.getElementById('products-container');
        categoryData.products.forEach((product) => {
            const productCard = new ProductCardComponent(productsContainer);
            productCard.render(
                product,
                (id) => this.mainPage.clickCard(id),
                (id) => this.mainPage.handleAddToCart(id)
            );
        });
    }
}