import { ButtonComponent } from '../button/index.js';

export class SubjectCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(item) {
        return (
            `
                <div class="card mt-4 me-4" style="width: 300px;" data-id="${item.id}">
                    <img class="card-img-top object-fit-cover" style="height: 10em;" src="${item.src}" alt="картинка">
                    <div class="card-body">
                        <h5 class="card-title">${item.title}</h5>
                    </div>
                </div>
            `
        );
    }

    render(item, btnCallback) {
        const html = this.getHTML(item);
        this.parent.insertAdjacentHTML('beforeend', html);
        const buttonParent = document.querySelector(`.card[data-id="${item.id}"] .card-body`);
        const productButton = new ButtonComponent(buttonParent);
        const btnData = { id: item.id, label: 'О предмете' };
        productButton.render(btnData, btnCallback);
    }
}
