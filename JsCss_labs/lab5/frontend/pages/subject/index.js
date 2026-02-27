import { BackButtonComponent } from '../../components/back-button/index.js';
import { ButtonComponent } from '../../components/button/index.js';
import { MainPage } from '../main/index.js';
import { ModulesPage } from '../modules/index.js';

export class SubjectPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('subject-page');
    }

    getHTML() {
        return '<div id="subject-page" class="mt-5 pb-5 d-flex flex-column align-items-center"></div>';
    }

    clickBack() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    clickModules() {
        const modulesPage = new ModulesPage(this.parent);
        modulesPage.render(this.data);
    }

    render(data) {
        this.data = data;

        this.parent.innerHTML = '';

        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backButton = new BackButtonComponent(this.pageRoot);
        backButton.render(this.clickBack.bind(this));

        const textHtml = `
            <h1 class="mt-4">${data.title}</h1>
            <p class="mb-5 w-50">${data.text}</p>
        `;
        this.pageRoot.insertAdjacentHTML('beforeend', textHtml);

        const modulesButton = new ButtonComponent(this.pageRoot);
        modulesButton.render({ id: 'modules-btn', label: 'Модули' }, this.clickModules.bind(this));
    }
}
