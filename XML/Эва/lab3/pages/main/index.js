import { ProductCardComponent } from "../../components/product_card/index.js";
import { ProductPage } from "../product/index.js";
import { CreateProductPage } from "../create_product/index.js";
import { ApiService } from "../../modules/apiService.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('main-page');
    }

    getHTML() {
        return `
            <div class="d-flex justify-content-between align-items-center mb-4">
                <h2>Список продуктов</h2>
                <button id="add-product-btn" class="btn btn-success">Добавить продукт</button>
            </div>
            <div id="main-page" class="d-flex flex-wrap"></div>
        `;
    }

    getData() {
        ApiService.getProducts((data) => {
            this.renderData(data);
        });
    }

    renderData(items) {
        items.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot);
            productCard.render(item, this.clickCard.bind(this));
        });
    }

    clickCard(e) {
        const cardId = e.target.dataset.id;
        const productPage = new ProductPage(this.parent, cardId);
        productPage.render();
    }

    clickAddProduct() {
        const createProductPage = new CreateProductPage(this.parent);
        createProductPage.render();
    }

    addListeners() {
        document.getElementById('add-product-btn').addEventListener('click', this.clickAddProduct.bind(this));
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);
        this.addListeners();
        this.getData();
    }
}