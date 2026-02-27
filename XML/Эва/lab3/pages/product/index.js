import { ProductComponent } from "../../components/product/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";
import { BadgesComponent } from "../../components/badges/index.js";
import { ApiService } from "../../modules/apiService.js";

export class ProductPage {
    constructor(parent, id) {
        this.parent = parent;
        this.id = id;
    }

    get pageRoot() {
        return document.getElementById('product-page');
    }

    getHTML() {
        return `
            <div id="product-page"></div>
        `;
    }

    getData() {
        ApiService.getProduct(this.id, (data) => {
            this.renderData(data);
        });
    }

    renderData(data) {
        const product = new ProductComponent(this.pageRoot);
        product.render(data);

        // Добавляем значок категории
        const badgeContainer = document.createElement('div');
        this.pageRoot.appendChild(badgeContainer);
        const badge = new BadgesComponent(badgeContainer);
        badge.render(data.category);

        // Добавляем цену
        const priceElement = document.createElement('p');
        priceElement.className = 'mt-3';
        priceElement.innerHTML = `<strong>Цена:</strong> ${data.price}`;
        this.pageRoot.appendChild(priceElement);
    }

    clickBack() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backButton = new BackButtonComponent(this.pageRoot);
        backButton.render(this.clickBack.bind(this));

        this.getData();
    }
}