import { ajax } from '../../../modules/ajax.js';
import { stockUrls } from '../../../modules/stockUrls.js';
import { CatPage } from '../cat/index.js';
export class EditPage {
    constructor(parent, id = null) {
        this.parent = parent;
        this.id = id;
        this.isEdit = id !== null;
    }

    getHTML() {
        return `
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container px-4 px-lg-5">
                    <a class="navbar-brand">${this.isEdit ? 'Редактирование' : 'Добавление'} кошки</a>
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation"><span class="navbar-toggler-icon"></span></button>
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                        <ul class="navbar-nav me-auto mb-2 mb-lg-0 ms-lg-4">
                            <li class="nav-item"><a class="nav-link active" aria-current="page" id="main">Главная</a></li>
                        </ul>
                    </div>
                </div>
            </nav>
            
            <div class="container mt-5">
                <form id="catForm">
                    <div class="mb-3">
                        <label for="name" class="form-label">Имя</label>
                        <input type="text" class="form-control" id="name" required>
                    </div>
                    <div class="mb-3">
                        <label for="image" class="form-label">Имя файла изображения</label>
                        <input type="text" class="form-control" id="image" required>
                    </div>
                    <div class="mb-3">
                        <label for="text" class="form-label">Описание</label>
                        <textarea class="form-control" id="text" rows="3" required></textarea>
                    </div>
                    <div class="mb-3">
                        <label for="price" class="form-label">Цена</label>
                        <input type="number" class="form-control" id="price" required>
                    </div>
                    <button type="submit" class="btn btn-primary">${this.isEdit ? 'Обновить' : 'Добавить'}</button>
                </form>
            </div>
        `;
    }

    loadData() {
        if (this.isEdit) {
            ajax.get(stockUrls.getStockById(this.id), (data) => {
                if (data) {
                    document.getElementById('name').value = data.name;
                    document.getElementById('image').value = data.image;
                    document.getElementById('text').value = data.text;
                    document.getElementById('price').value = data.price;
                }
            });
        }
    }

    handleSubmit() {
        const form = document.getElementById('catForm');
        form.addEventListener('submit', (e) => {
            e.preventDefault();
            
            const catData = {
                name: document.getElementById('name').value,
                image: document.getElementById('image').value,
                text: document.getElementById('text').value,
                price: document.getElementById('price').value
            };

            if (this.isEdit) {
                ajax.put(stockUrls.getStockById(this.id), catData, (data, status) => {
                    if (status === 200) {
                        alert('Кошка успешно обновлена!');
                        new CatPage(this.parent).render();
                    }
                });
            } else {
                ajax.post(stockUrls.getStocks(), catData, (data, status) => {
                    if (status === 201) {
                        alert('Кошка успешно добавлена!');
                        new CatPage(this.parent).render();
                    }
                });
            }
        });
    }

    render() {
        this.parent.innerHTML = this.getHTML();
        this.loadData();
        this.handleSubmit();
        
     
        this.parent.addEventListener('click', (e) => {
            if (e.target.id === 'main') {
                e.preventDefault();
                new CatPage(this.parent).render();
            }
        });
    }
}