import { ProductCardComponent } from "../../components/product_card/index.js";
import { BackButtonComponent } from "../../components/back_button/index.js";
import { MainPage } from "../main/index.js";
import { ajax } from "../../modules/ajax.js";
import { stockUrls } from "../../modules/stockUrls.js";

export class CategoryPage {
    constructor(parent, category) {
        this.parent = parent;
        this.category = category;
    }

    getHTML() {
        return `
            <div id="category-page">
                <div id="back-button-container"></div>
                <h2 class="mb-4">${this.category}</h2>
                <div class="d-flex flex-wrap justify-content-center gap-4" id="products-container">
                    <div class="text-center w-100 my-4">
                        <div class="spinner-border text-primary" role="status">
                            <span class="visually-hidden">Загрузка...</span>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    loadProducts() {
        const container = document.getElementById('products-container');
        
        console.log(`Загрузка товаров категории "${this.category}"...`);
        
        ajax.get(stockUrls.getStocks(), (data, status) => {
            console.log('Ответ сервера:', { status, data });
            
            if (status === 200 && data) {
                const filtered = data.filter(item => 
                    item.category?.toLowerCase() === this.category.toLowerCase()
                );
                
                if (filtered.length === 0) {
                    container.innerHTML = `
                        <div class="alert alert-info w-100">
                            В категории "${this.category}" пока нет товаров
                        </div>
                    `;
                    return;
                }
                
                container.innerHTML = '';
                filtered.forEach(item => {
                    const card = new ProductCardComponent(container);
                    card.render(item, (id) => {
                        const productPage = new ProductPage(this.parent, id);
                        productPage.render();
                    });
                });
            } else {
                container.innerHTML = `
                    <div class="alert alert-danger w-100">
                        Ошибка загрузки: ${status || 'Нет соединения с сервером'}
                        <button class="btn btn-sm btn-secondary mt-2" id="retry-btn">
                            Повторить попытку
                        </button>
                    </div>
                `;
                document.getElementById('retry-btn').addEventListener('click', () => this.loadProducts());
            }
        });
    }

    render() {
        this.parent.innerHTML = this.getHTML();
        
        new BackButtonComponent(document.getElementById('back-button-container'))
            .render(() => {
                const mainPage = new MainPage(this.parent);
                mainPage.render();
            });

        this.loadProducts();
    }
}