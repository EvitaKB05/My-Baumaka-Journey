import { ajax } from "../../modules/ajax.js";
import { stockUrls } from "../../modules/stockUrls.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";

/**
 * Страница создания новой акции
 */
export class CreateStockPage {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return `
            <div id="create-stock-page">
                <div id="back-button-container"></div>
                <h2 class="mb-4">Добавить продукт</h2>
                <form id="create-stock-form">
                    <div class="mb-3">
                        <label for="title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="title" required>
                    </div>
                    <div class="mb-3">
                        <label for="text" class="form-label">Описание</label>
                        <textarea class="form-control" id="text" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="src" class="form-label">URL изображения</label>
                        <input type="url" class="form-control" id="src" required>
                    </div>
                    <div class="mb-3">
                        <label for="category" class="form-label">Категория</label>
                        <select class="form-select" id="category" required>
                            <option value="Мясо">Мясо</option>
                            <option value="Овощи">Овощи</option>
                            <option value="Фрукты">Фрукты</option>
                            <option value="Молочные Продукты">Молочные Продукты</option>
                        </select>
                    </div>
                    <button type="submit" class="btn btn-primary">Создать</button>
                </form>
            </div>
        `;
    }

    handleSubmit(e) {
        e.preventDefault();
        
        const data = {
            title: document.getElementById('title').value,
            text: document.getElementById('text').value,
            src: document.getElementById('src').value,
            category: document.getElementById('category').value
        };

        ajax.post(stockUrls.createStock(), data, (response, status) => {
            if (status === 201) {
                alert('Акция успешно создана!');
                const mainPage = new MainPage(this.parent);
                mainPage.render();
            } else {
                alert('Ошибка при создании акции');
            }
        });
    }

    render() {
        this.parent.innerHTML = '';
        this.parent.insertAdjacentHTML('beforeend', this.getHTML());

        new BackButtonComponent(document.getElementById('back-button-container'))
            .render(() => {
                const mainPage = new MainPage(this.parent);
                mainPage.render();
            });

        document.getElementById('create-stock-form')
            .addEventListener('submit', this.handleSubmit.bind(this));
    }
}