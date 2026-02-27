import { BadgesComponent } from "../badges/index.js";

export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getProductImage(title) {
        const productImages = {
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
            'Сливочное масло': 'butter.jpg',
        };
        
        return `static/images/${productImages[title] || 'hamster.jpg'}`;
    }

    getHTML(data) {
        const imgSrc = this.getProductImage(data.title);
        
        return `
            <div class="card" style="width: 300px; margin: 10px;">
                <img class="card-img-top" src="${imgSrc}" alt="${data.title}" 
                     style="height: 200px; object-fit: cover;"
                     onerror="this.src='static/images/hamster.jpg'">
                <div class="card-body">
                    <h5 class="card-title">${data.title}</h5>
                    <div id="badge-${data.id}"></div>
                    <p class="card-text">${data.text}</p>
                    <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Подробнее</button>
                </div>
            </div>
        `;
    }

    addListeners(data, listener) {
        document
            .getElementById(`click-card-${data.id}`)
            .addEventListener("click", listener);
    }

    render(data, listener) {
        const html = this.getHTML(data);
        this.parent.insertAdjacentHTML('beforeend', html);
        this.addListeners(data, listener);
        
        // Добавляем значок для категории продукта
        const badgeContainer = document.getElementById(`badge-${data.id}`);
        const badge = new BadgesComponent(badgeContainer);
        badge.render(data.category);
    }
}