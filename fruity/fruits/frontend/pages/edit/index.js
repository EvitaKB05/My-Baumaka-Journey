import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";

export class EditPage {
    constructor(parent, productId) {
        this.parent = parent;
        this.productId = productId;
        this.product = null;
        this.categories = [];
    }

    getHTML() {
        if (!this.product) return '<div>Загрузка...</div>';

        return `
            <div id="edit-page">
                <div id="back-button-container"></div>
                <h2 class="text-center mb-4">Редактировать продукт</h2>
                <form id="edit-form" class="mx-auto" style="max-width: 500px;">
                    <div class="mb-3">
                        <label for="title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="title" 
                               value="${this.product.title}" required>
                    </div>
                    <div class="mb-3">
                        <label for="description" class="form-label">Описание</label>
                        <textarea class="form-control" id="description" rows="3" required>${this.product.text}</textarea>
                    </div>
                    <div class="mb-3">
                        <label for="price" class="form-label">Цена</label>
                        <input type="number" class="form-control" id="price" 
                               value="${this.product.price || ''}" required>
                    </div>
                    <div class="mb-3">
                        <label for="category" class="form-label">Категория</label>
                        <select class="form-select" id="category" required>
                            ${this.categories.map(cat => 
                                `<option value="${cat.id}" ${cat.title === this.product.category ? 'selected' : ''}>
                                    ${cat.title}
                                </option>`
                            ).join('')}
                        </select>
                    </div>
                    <div class="mb-3">
                        <label for="imageUrl" class="form-label">URL изображения</label>
                        <input type="url" class="form-control" id="imageUrl" 
                               value="${this.product.src}" 
                               placeholder="Оставьте пустым для изображения по умолчанию">
                    </div>
                    <div class="d-flex gap-2">
                        <button type="submit" class="btn btn-primary flex-grow-1">Сохранить</button>
                        
                    </div>
                </form>
            </div>
        `;
    }

    getData() {
        const mainPage = new MainPage(this.parent);
        return mainPage.getData();
    }

    findProduct() {
        const categories = this.getData();
        for (const category of categories) {
            const product = category.products.find(p => p.id === this.productId);
            if (product) {
                product.category_id = category.id; // Добавляем ID категории
                return product;
            }
        }
        return null;
    }

    handleSubmit(e) {
        e.preventDefault();
        
        const title = document.getElementById('title').value;
        const description = document.getElementById('description').value;
        const price = parseFloat(document.getElementById('price').value);
        const categoryTitle = document.getElementById('category').selectedOptions[0].text;
        let imageUrl = document.getElementById('imageUrl').value;

        if (!imageUrl) {
            imageUrl = 'static/images/hamster.jpg';
        }

        // Обновляем данные продукта
        this.product.title = title;
        this.product.text = description;
        this.product.price = price;
        this.product.src = imageUrl;
        this.product.category = categoryTitle;

        alert('Продукт успешно обновлен!');
        
        // Возвращаемся на главную страницу
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    /*handleDelete() {
        if (confirm('Вы уверены, что хотите удалить этот продукт?')) {
            const categories = this.getData();
            for (const category of categories) {
                const index = category.products.findIndex(p => p.id === this.productId);
                if (index !== -1) {
                    category.products.splice(index, 1);
                    break;
                }
            }

            alert('Продукт успешно удален!');
            const mainPage = new MainPage(this.parent);
            mainPage.render();
        }
    }
    */
    async render() {
        // Получаем категории из MainPage
        const categoriesData = this.getData();
        this.categories = categoriesData.map(category => ({
            id: category.id,
            title: category.title
        }));

        // Находим продукт
        this.product = this.findProduct();

        if (!this.product) {
            alert('Продукт не найден');
            const mainPage = new MainPage(this.parent);
            mainPage.render();
            return;
        }

        this.parent.innerHTML = '';
        this.parent.insertAdjacentHTML('beforeend', this.getHTML());

        const backButton = new BackButtonComponent(document.getElementById('back-button-container'));
        backButton.render(() => {
            const mainPage = new MainPage(this.parent);
            mainPage.render();
        });

        document.getElementById('edit-form').addEventListener('submit', (e) => this.handleSubmit(e));
        document.getElementById('delete-btn').addEventListener('click', () => this.handleDelete());
    }
}