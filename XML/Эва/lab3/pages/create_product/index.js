import { MainPage } from "../main/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { ApiService } from "../../modules/apiService.js";

export class CreateProductPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('create-product-page');
    }

    getHTML() {
        return `
            <div id="create-product-page">
                <div class="mb-3">
                    <h2>Добавить новый продукт</h2>
                </div>
                <form id="create-product-form">
                    <div class="mb-3">
                        <label for="product-title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="product-title" required>
                    </div>
                    <div class="mb-3">
                        <label for="product-text" class="form-label">Описание</label>
                        <textarea class="form-control" id="product-text" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="product-category" class="form-label">Категория</label>
                        <select class="form-select" id="product-category" required>
                            <option value="">Выберите категорию</option>
                            <option value="Мясо">Мясо</option>
                            <option value="Овощи">Овощи</option>
                            <option value="Фрукты">Фрукты</option>
                            <option value="Молочные Продукты">Молочные Продукты</option>
                        </select>
                    </div>
                    <div class="mb-3">
                        <label for="product-price" class="form-label">Цена</label>
                        <input type="text" class="form-control" id="product-price" required>
                    </div>
                    <button type="submit" class="btn btn-primary">Создать</button>
                </form>
            </div>
        `;
    }

    clickBack() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    handleSubmit(e) {
        e.preventDefault();
        
        const productData = {
            title: document.getElementById('product-title').value,
            text: document.getElementById('product-text').value,
            category: document.getElementById('product-category').value,
            price: document.getElementById('product-price').value,
            src: 'static/images/hamster.jpg' // Дефолтное изображение
        };

        ApiService.createProduct(productData, (data, status) => {
            if (status === 201) {
                alert('Продукт успешно создан!');
                const mainPage = new MainPage(this.parent);
                mainPage.render();
            } else {
                alert('Ошибка при создании продукта');
            }
        });
    }

    addListeners() {
        document.getElementById('create-product-form').addEventListener('submit', this.handleSubmit.bind(this));
    }

    render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backButton = new BackButtonComponent(this.pageRoot);
        backButton.render(this.clickBack.bind(this));

        this.addListeners();
    }
}