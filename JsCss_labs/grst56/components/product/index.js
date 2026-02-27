/**
 * Компонент детального отображения продукта
 */
export class ProductComponent {
    constructor(parent) {
        this.parent = parent;
    }
  
    getHTML(data) {
        // используем хомячка если нет соответствующей пикчи
        const imageSrc = data.src || 'static/images/hamster.jpg';
        
        return (
            `
                <div class="card mb-3" style="width: 540px;">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${imageSrc}" 
                                 class="img-fluid" 
                                 alt="${data.title || 'Изображение продукта'}"
                                 style="height: 100%; object-fit: cover;"
                                 onerror="this.src='static/images/hamster.jpg'">
                        </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">${data.title}</h5>
                                <p class="card-text">${data.text}</p>
                                ${data.price ? `<p class="card-text"><small class="text-muted">Цена: ${data.price}</small></p>` : ''}
                            </div>
                        </div>
                    </div>
                </div>
            `
        );
    }
  
    render(data) {
        const html = this.getHTML(data);
        this.parent.insertAdjacentHTML('beforeend', html);
    }
}