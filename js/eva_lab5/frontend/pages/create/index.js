import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";

export class CreatePage {
    constructor(parent) {
        this.parent = parent;
        this.categories = [];
    }

    getHTML() {
        return `
            <div id="create-page">
                <div id="back-button-container"></div>
                <h2 class="text-center mb-4">Добавить новый продукт</h2>
                <form id="create-form" class="mx-auto" style="max-width: 500px;">
                    <div class="mb-3">
                        <label for="title" class="form-label">Название</label>
                        <input type="text" class="form-control" id="title" required>
                    </div>
                    <div class="mb-3">
                        <label for="description" class="form-label">Описание</label>
                        <textarea class="form-control" id="description" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="price" class="form-label">Цена</label>
                        <input type="number" class="form-control" id="price" min="0" step="0.01" required>
                    </div>
                    <div class="mb-3">
                        <label for="category" class="form-label">Категория</label>
                        <select class="form-select" id="category" required>
                            <option value="" selected disabled>Выберите категорию</option>
                            ${this.categories.map(cat => 
                                `<option value="${cat.id}">${cat.title}</option>`
                            ).join('')}
                        </select>
                    </div>
                    <div class="mb-3">
                        <label for="imageUrl" class="form-label">URL изображения</label>
                        <input type="url" class="form-control" id="imageUrl" 
                               placeholder="Оставьте пустым для изображения по умолчанию">
                    </div>
                    <button type="submit" class="btn btn-primary w-100">Добавить продукт</button>
                </form>
            </div>
        `;
    }

    getCategories() {
        // Получаем данные из localStorage или создаем новые
        const savedData = localStorage.getItem('storeData');
        return savedData ? JSON.parse(savedData) : new MainPage(this.parent).getData();
    }

    saveCategories(data) {
        // Сохраняем обновленные данные в localStorage
        localStorage.setItem('storeData', JSON.stringify(data));
    }

    generateUniqueId(categories) {
        // Генерируем уникальный ID для продукта
        const allProducts = categories.flatMap(cat => cat.products);
        let newId;
        do {
            newId = Math.floor(Math.random() * 1000000);
        } while (allProducts.some(p => p.id === newId));
        return newId;
    }

    handleSubmit(e) {
        e.preventDefault();
        
        // Получаем значения из формы
        const title = document.getElementById('title').value.trim();
        const description = document.getElementById('description').value.trim();
        const price = parseFloat(document.getElementById('price').value);
        const categoryId = parseInt(document.getElementById('category').value);
        let imageUrl = document.getElementById('imageUrl').value.trim();

        // Валидация данных
        if (!title || !description || isNaN(price) || price < 0 || isNaN(categoryId)) {
            alert('Пожалуйста, заполните все обязательные поля корректно');
            return;
        }

        // Устанавливаем изображение по умолчанию, если не указано
        if (!imageUrl) {
            imageUrl = 'static/images/hamster.jpg';
        }

        // Получаем текущие данные
        const categories = this.getCategories();
        const selectedCategory = categories.find(cat => cat.id === categoryId);

        if (!selectedCategory) {
            alert('Ошибка: категория не найдена');
            return;
        }

        // Создаем новый продукт
        const newProduct = {
            id: this.generateUniqueId(categories),
            title,
            text: description,
            price,
            src: imageUrl,
            category: selectedCategory.title
        };

        // Добавляем продукт в категорию
        selectedCategory.products.push(newProduct);

        // Сохраняем обновленные данные
        this.saveCategories(categories);

        // Показываем уведомление и возвращаемся на главную
        alert(`Продукт "${title}" успешно добавлен в категорию "${selectedCategory.title}"!`);
        
        // Возвращаемся на главную страницу с обновленными данными
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    async render() {
        // Получаем категории для формы
        const categoriesData = this.getCategories();
        this.categories = categoriesData.map(category => ({
            id: category.id,
            title: category.title
        }));

        // Очищаем и рендерим форму
        this.parent.innerHTML = '';
        this.parent.insertAdjacentHTML('beforeend', this.getHTML());

        // Добавляем кнопку "Назад"
        const backButton = new BackButtonComponent(document.getElementById('back-button-container'));
        backButton.render(() => {
            const mainPage = new MainPage(this.parent);
            mainPage.render();
        });

        // Вешаем обработчик на форму
        document.getElementById('create-form').addEventListener('submit', (e) => this.handleSubmit(e));
    }
}