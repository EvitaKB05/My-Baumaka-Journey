export class CategoryCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(category) {
        const categoryImages = {
            'Мясо': 'static/images/meat_category.jpg',
            'Овощи': 'static/images/vegetables_category.jpg',
            'Фрукты': 'static/images/fruits_category.jpg',
            'Молочные Продукты': 'static/images/dairy_category.jpg'
        };

        const imageSrc = categoryImages[category] || 'static/images/hamster.jpg';
        
        return `
            <div class="card" style="width: 300px; margin: 10px; cursor: pointer;">
                <img src="${imageSrc}" 
                     class="card-img-top" 
                     alt="${category}"
                     style="height: 200px; object-fit: cover;"
                     onerror="this.src='static/images/hamster.jpg'">
                <div class="card-body">
                    <h5 class="card-title text-center">${category}</h5>
                </div>
            </div>
        `;
    }

    addListeners(listener, category) {
        this.parent.lastElementChild.addEventListener("click", () => listener(category));
    }

    render(category, listener) {
        const html = this.getHTML(category);
        this.parent.insertAdjacentHTML('beforeend', html);
        this.addListeners(listener, category);
    }
}