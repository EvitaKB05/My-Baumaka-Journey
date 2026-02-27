import { BadgesComponent } from "../badges/index.js";

export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getProductImage(data) {
        // Проверяем наличие изображения в данных продукта
        if (data.src && data.src.startsWith('static/images/')) {
            return data.src;
        }
        
        // Если изображения нет, используем соответствие по названию
        const imageMap = {
            'Говядина': 'beef.jpg',
            'Баранина': 'lamb.jpg',
            'Курица': 'chicken.jpg',
            'Морковь': 'carrots.jpg',
            'Твинк': 'twink.jpg',
            'Помидоры': 'tomatoes.jpg',
            'Апельсины': 'oranges.jpg',
            'Бананы': 'bananas.jpg',
            'Яблоки': 'apples.jpg',
            'Молоко': 'milk.jpg',
            'Сыр': 'cheese.jpg',
            'Сливочное масло': 'butter.jpg'
        };

        const imageName = imageMap[data.title] || 'hamster.jpg';
        return `static/images/${imageName}`;
    }

    getHTML(data) {
        const imageSrc = this.getProductImage(data);
        
        return `
            <div class="card" style="width: 300px; margin: 10px;">
                <img src="${imageSrc}" 
                     class="card-img-top" 
                     alt="${data.title}"
                     style="height: 200px; object-fit: cover;"
                     onerror="this.src='static/images/hamster.jpg'">
                <div class="card-body">
                    <h5 class="card-title">${data.title}</h5>
                    <div id="badge-${data.id}"></div>
                    <p class="card-text">${data.text}</p>
                    <button class="btn btn-primary" id="details-${data.id}">Подробнее</button>
                </div>
            </div>
        `;
    }

    addListeners(data, clickDetailsListener) {
        document
            .getElementById(`details-${data.id}`)
            .addEventListener("click", () => clickDetailsListener(data.id));
    }

    render(data, clickDetailsListener) {
        const html = this.getHTML(data);
        this.parent.insertAdjacentHTML('beforeend', html);
        this.addListeners(data, clickDetailsListener);
        
        const badgeContainer = document.getElementById(`badge-${data.id}`);
        const badge = new BadgesComponent(badgeContainer);
        badge.render(data.category);
    }
}