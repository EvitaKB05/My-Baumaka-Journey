export class CategoryCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    render(category, onClick) {
        if (!category || typeof category !== 'object') {
            console.error('Invalid category data received:', category);
            return;
        }

        const card = document.createElement('div');
        card.className = 'card';
        card.style.width = '300px';
        card.style.cursor = 'pointer';
        card.style.margin = '15px';
        card.style.boxShadow = '0 4px 8px rgba(0,0,0,0.1)';
        
        // Обработка изображения
        const imgSrc = category.src || '/static/images/default_category.jpg';
        const imgAlt = category.title || 'Категория товаров';
        
        card.innerHTML = `
            <img src="${imgSrc}" 
                 class="card-img-top" 
                 alt="${imgAlt}"
                 style="height: 200px; object-fit: cover;"
                 onerror="this.src='/static/images/default_category.jpg';">
            <div class="card-body">
                <h5 class="card-title text-center">${category.title || 'Категория'}</h5>
            </div>
        `;
        
        card.addEventListener('click', () => {
            if (typeof onClick === 'function') {
                onClick();
            }
        });
        
        this.parent.appendChild(card);
    }
}