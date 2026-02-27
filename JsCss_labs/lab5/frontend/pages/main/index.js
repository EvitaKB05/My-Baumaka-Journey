import { ajax } from '../../modules/ajax.js';
import { SubjectCardComponent } from '../../components/subject-card/index.js';
import { SubjectPage } from '../subject/index.js';
import { subjectUrls } from '../../modules/subjectUrls.js';

export class MainPage {
    constructor(parent) {
        this.parent = parent;
        this.page = 1;
        this.perPage = 100;
    }

    get cardsRoot() {
        return document.getElementById('subject-cards');
    }

    getHTML() {
        return (
            `
                <div id="main-page" class="mt-5 pb-5 d-flex flex-column align-items-center">
                    <h1>Учебные предметы</h1>
                    <div class="mt-5 d-flex flex-row align-items-center">
                        <h5 class="mb-0 me-3">Поиск</h5>
                        <input id="search-input" class="form-control" type="text" placeholder="Введите название">
                    </div>
                    <div class="mt-2 d-flex flex-row align-items-center">
                        <h5 class="mb-0 me-3" style="text-wrap: nowrap;">Размер страницы</h5>
                        <input id="perPage-input" class="form-control" type="text" placeholder="Введите число">
                    </div>
                    <div id="subject-cards" class="w-75 mt-5 d-flex flex-wrap justify-content-around"></div>
                    <nav class="mt-5" aria-label="Page navigation" style="user-select: none;">
                        <ul class="pagination" id="page-list"></ul>
                    </nav>
                </div>
            `
        );
    }

    getData() {
        const searchTitle = document.getElementById('search-input').value;
        return new Promise((resolve, reject) => {
            ajax.get(subjectUrls.getSubjects(searchTitle), (data, status) => {
                if (status != 200) {
                    reject(`API вернуло код ${status}`);
                    return;
                }
                resolve(data);
            });
        });
    }

    clickCard(e) {
        const cardId = e.target.dataset.id;
        const subject = this.items.filter((sub) => sub.id == cardId)[0];
        const subjectPage = new SubjectPage(this.parent);
        subjectPage.render(subject);
    }

    async renderItems() {
        this.cardsRoot.innerHTML = '';
        const start = (this.page - 1) * this.perPage;
        const stop = Math.min(this.page * this.perPage, this.items.length);

        for (let i = start; i < stop; i++) {
            const productCard = new SubjectCardComponent(this.cardsRoot);
            productCard.render(this.items[i], this.clickCard.bind(this));
        }
    }

    isNaturalNumber(n) {
        n = n.toString();
        var n1 = Math.abs(n),
            n2 = parseInt(n, 10);
        return n2 > 0 && !isNaN(n1) && n2 === n1 && n1.toString() === n;
    }

    renderPage() {
        const perPageInput = document.getElementById('perPage-input');
        if (!this.isNaturalNumber(perPageInput.value.trim())) {
            return;
        }

        this.perPage = parseInt(perPageInput.value);
        const pageCount = Math.ceil(this.items.length / this.perPage);
        if (this.page > pageCount) {
            this.page = pageCount;
        }

        const pageList = document.getElementById('page-list');
        pageList.innerHTML = '';

        pageList.insertAdjacentHTML('beforeend', `<li class="page-item${(this.page == 1) ? ' disabled' : ''}"><a class="page-link" href="#">Previous</a></li>`);
        pageList.children[pageList.children.length - 1].addEventListener('click', () => {
            if (this.page == 1) {
                return;
            }
            this.page -= 1;
            this.renderPage();
        });

        for (let i = 1; i <= pageCount; i++) {
            pageList.insertAdjacentHTML('beforeend', `<li class="page-item${(i == this.page) ? ' active' : ''}"><a class="page-link" href="#">${i}</a></li>`);
            pageList.children[pageList.children.length - 1].addEventListener('click', () => {
                this.page = i;
                this.renderPage();
            });
        }

        pageList.insertAdjacentHTML('beforeend', `<li class="page-item${(this.page == pageCount) ? ' disabled' : ''}"><a class="page-link" href="#">Next</a></li>`);
        pageList.children[pageList.children.length - 1].addEventListener('click', () => {
            if (this.page == pageCount) {
                return;
            }
            this.page += 1;
            this.renderPage();
        });

        this.renderItems();
    }

    async render() {
        this.parent.innerHTML = '';
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);
        document.getElementById('perPage-input').value = this.perPage;

        document.getElementById('search-input').addEventListener('input', async () => {
            const title = document.getElementById('search-input').value;
            this.items = await this.getData(title);
            this.renderPage();
        });
        document.getElementById('perPage-input').addEventListener('input', this.renderPage.bind(this));

        this.items = await this.getData();

        this.renderPage();
    }
}
