export class Carousel {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(items) {
        items[0].active = true;
        const htmlItems = items.map((item) =>
            `
                <div class="carousel-item${item.active ? ' active' : ''}">
                    <img style="background-color: gray; height: 20em;" src="${item.src}" class="d-block w-100 object-fit-cover" alt="${item.title}">
                    <div class="carousel-caption d-none d-md-block">
                        <h5 style="text-shadow: 0 0 1em black;">${item.title}</h5>
                    </div>
                </div>
            `
        );
        return (
            `
                <div id="module-carousel" class="carousel slide w-100" data-bs-ride="false">
                    <div class="carousel-indicators">
                        <button type="button" data-bs-target="#module-carousel" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
                        <button type="button" data-bs-target="#module-carousel" data-bs-slide-to="1" aria-label="Slide 2"></button>
                        <button type="button" data-bs-target="#module-carousel" data-bs-slide-to="2" aria-label="Slide 3"></button>
                    </div>
                    <div class="carousel-inner">
                        ${htmlItems.join('\n')}
                    </div>
                    <button class="carousel-control-prev" type="button" data-bs-target="#module-carousel" data-bs-slide="prev">
                        <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                        <span class="visually-hidden">Предыдущий</span>
                    </button>
                    <button class="carousel-control-next" type="button" data-bs-target="#module-carousel" data-bs-slide="next">
                        <span class="carousel-control-next-icon" aria-hidden="true"></span>
                        <span class="visually-hidden">Следующий</span>
                    </button>
                </div>
            `
        );
    }

    render(items) {
        const html = this.getHTML(items);
        this.parent.insertAdjacentHTML('beforeend', html);
    }
}
