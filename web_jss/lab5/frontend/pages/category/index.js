import { ProductCardComponent } from "../../components/product_card/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";

export class CategoryPage {
    constructor(parent, category) {
        this.parent = parent;
        this.category = category;
    }

    get pageRoot() {
        return document.getElementById('category-page');
    }

    getHTML() {
        return `
            <div id="category-page">
                <div id="back-button-container"></div>
                <h2 class="mb-4">${this.category}</h2>
                <div class="d-flex flex-wrap" id="products-container"></div>
            </div>
        `;
    }

    clickBack() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backButtonContainer = document.getElementById('back-button-container');
        const backButton = new BackButtonComponent(backButtonContainer);
        backButton.render(this.clickBack.bind(this));

        const mainPage = new MainPage(this.parent);
        const data = mainPage.getData().filter(item => item.category === this.category);

        const productsContainer = document.getElementById('products-container');
        data.forEach((item) => {
            const productCard = new ProductCardComponent(productsContainer);
            productCard.render(item, mainPage.clickCard.bind(mainPage));
        });
    }
}