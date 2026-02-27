import { ButtonComponent } from './../../components/cat-page/index.js'
import { AlertComponent } from './../../components/alert/index.js'
import { CalcPage } from './../calc/index.js'
import { AuthorPage } from './../author/index.js'
import { EditPage } from './../edit/index.js'
import { LabPage } from './../labs/index.js'
import { ajax } from '../../modules/ajax.js'
import { stockUrls } from '../../modules/stockUrls.js'

import data from "../../assets/data.json" with { type: "json" }

export class CatPage{
    constructor(parent) {
        this.parent = parent
        this.cats = []
    }

    getData() {
        ajax.get(stockUrls.getStocks(), (data) => {
            if (data) {
                this.cats = data
                this.renderCards()
            }
        })
    }

    renderCards() {
        const container = this.parent.querySelector('.row.gx-4.gx-lg-5.row-cols-2.row-cols-md-3.row-cols-xl-4');
        if (container) {
            container.innerHTML = '';
            this.cats.forEach(cat => {
                const cardHTML = `
                    <div class="col mb-5">
                        <div class="card h-100">
                            <img class="card-img-top" src="${stockUrls.getCatImage(cat.image)}" alt="${cat.name}" loading="lazy" />
                            <div class="card-body p-4">
                                <div class="text-center">
                                    <h5 class="fw-bolder">${cat.name}</h5>
                                    ${cat.oldPrice ? `<span class="text-muted text-decoration-line-through">$${cat.oldPrice}.00</span>` : ''}
                                    $${cat.price}.00
                                </div>
                            </div>
                            <div class="card-footer p-4 pt-0 border-top-0 bg-transparent">
                                <div class="text-center">
                                    <a class="btn btn-outline-dark mt-auto" id="view-${cat.id}">Подробнее</a>
                                    <a class="btn btn-outline-warning mt-auto" id="edit-${cat.id}">Редактировать</a>
                                    <a class="btn btn-outline-danger mt-auto" id="delete-${cat.id}">Удалить</a>
                                </div>
                            </div>
                        </div>
                    </div>
                `;
                container.insertAdjacentHTML('beforeend', cardHTML);
            });
            this.subscribeButtons();
        }
    }

    // Обновим subscribeButtons():
    subscribeButtons() {
        this.cats.forEach(cat => {

            document.getElementById(`view-${cat.id}`).addEventListener("click", () => {
                this.chooseCatIndex(this.parent, cat.id)
            });
            
            document.getElementById(`edit-${cat.id}`).addEventListener("click", () => {
                new EditPage(this.parent, cat.id).render();
            });
            
            document.getElementById(`delete-${cat.id}`).addEventListener("click", () => {
                if (confirm(`Удалить кошку ${cat.name}?`)) {
                    ajax.delete(stockUrls.getStockById(cat.id), (data, status) => {
                        if (status === 200) {
                            // 1. Удаляем из DOM
                            const card = document.querySelector(`[id^="view-${cat.id}"]`)?.closest('.col.mb-5');
                            if (card) card.remove();
                            
                            // 2. Обновляем локальные данные
                            this.cats = this.cats.filter(c => c.id !== cat.id);
                            
                            alert('Кошка удалена!');
                        } else {
                            alert(`Ошибка удаления: ${status}`);
                        }
                    });
                }
            });
        });

        document.getElementById('add').addEventListener('click', () => {
            new EditPage(this.parent).render();
        });
    }

    listen(){
        document.getElementById('main').addEventListener("click", ()=>{this.render(()=>{this.listen();})})
        document.getElementById('lab').addEventListener("click", ()=>{new LabPage(this.parent).render(()=>{this.listen();})})
        document.getElementById('author').addEventListener("click", ()=>{new AuthorPage(this.parent).render(()=>{this.listen();})})
        document.getElementById('calc').addEventListener("click", ()=>{new CalcPage(this.parent).render(()=>{this.listen();})})
    }

    chooseCatIndex(target,id){
        new ButtonComponent(target, id).render(()=>{
            document.getElementById('main').addEventListener("click", ()=>{new CatPage(target).render()})
            document.getElementById('back').addEventListener("click", ()=>{new CatPage(target).render()})
        })
        new AlertComponent(target, data.cats[id-1].name).render()
    }

    render() {
        this.parent.innerHTML = this.getHTML()
        this.getData() 
        this.listen()
    }
    getHTML() {
        return (`
            <!-- Navigation -->
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container px-4 px-lg-5">
                    <a class="navbar-brand">Кошкомаркет</a>
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse"
                            data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent"
                            aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                        <ul class="navbar-nav me-auto mb-2 mb-lg-0 ms-lg-4">
                            <li class="nav-item"><a class="nav-link active" id="main">Главная</a></li>
                            <li class="nav-item"><a class="nav-link" id="calc">Калькулятор</a></li>
                            <li class="nav-item dropdown">
                                <a class="nav-link dropdown-toggle" id="navbarDropdown" role="button"
                                   data-bs-toggle="dropdown" aria-expanded="false">Информация</a>
                                <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                                    <li><a class="dropdown-item" id="lab">Все лабы</a></li>
                                    <li><hr class="dropdown-divider"/></li>
                                    <li><a class="dropdown-item" id="author">Об авторе</a></li>
                                </ul>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
    
            <!-- Header -->
            <header class="bg-dark py-5">
                <div class="container px-4 px-lg-5 my-5">
                    <div class="text-center text-white">
                        <h1 class="display-4 fw-bolder">Кошкомаркет</h1>
                        <p class="lead fw-normal text-white-50 mb-0">Специально для тебя</p>
                    </div>
                </div>
            </header>
    
            <!-- Section (cards will be rendered here) -->
            <section class="py-5">
                <div class="container px-4 px-lg-5 mt-5">
                    <button id="add" class="btn btn-outline-success mb-4">+ Добавить кошку</button>
                    <div class="row gx-4 gx-lg-5 row-cols-2 row-cols-md-3 row-cols-xl-4 justify-content-center"></div>
                </div>
            </section>
        `);
    }
    
}