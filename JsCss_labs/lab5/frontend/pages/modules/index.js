import { BackButtonComponent } from '../../components/back-button/index.js';
import { ButtonComponent } from '../../components/button/index.js';
import { MainPage } from '../main/index.js';
import { Carousel } from '../../components/carousel/index.js';
import { SubjectPage } from '../subject/index.js';

export class ModulesPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('modules-page');
    }

    getHTML() {
        return '<div id="modules-page" class="mt-5 pb-5 gap-4 d-flex flex-column align-items-center"></div>';
    }

    clickBackMain() {
        const mainPage = new MainPage(this.parent);
        mainPage.render();
    }

    clickBack() {
        const subjectPage = new SubjectPage(this.parent);
        subjectPage.render(this.data);
    }

    render(data) {
        this.data = data;

        this.parent.innerHTML = '';

        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);

        const backMainButton = new ButtonComponent(this.pageRoot);
        backMainButton.render({ id: 'main-page-btn', label: 'На главную' }, this.clickBackMain.bind(this));

        const backButton = new BackButtonComponent(this.pageRoot);
        backButton.render(this.clickBack.bind(this));

        this.pageRoot.insertAdjacentHTML('beforeend', '<h1>Модули</h1>');

        const moduleCarousel = new Carousel(this.pageRoot);
        moduleCarousel.render(data.modules);
    }
}
