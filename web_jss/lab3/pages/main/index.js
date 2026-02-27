import { ProductCardComponent } from "../../components/product_card/index.js";
import { ProductPage } from "../product/index.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    };

    get pageRoot() {
        return document.getElementById('main-page')
    }

    getHTML() {
        return (
            `
                <div id="main-page" class="d-flex flex-wrap"><div/>
            `
        )
    }

    getData() {
        return [
            // Мясо
            {
                id: 1,
                src: "/static/images/beef.jpg",
                title: "Говядина",
                text: "Свежая говядина",
                category: "Мясо"
            },
            {
                id: 2,
                src: "/static/images/lamb.jpg",
                title: "Баранина",
                text: "Нежная баранина",
                category: "Мясо"
            },
            {
                id: 3,
                src: "/static/images/chicken.jpg",
                title: "Курица",
                text: "Куриные грудки",
                category: "Мясо"
            },
            // Овощи
            {
                id: 4,
                src: "/static/images/carrots.jpg",
                title: "Морковь",
                text: "Свежая морковь",
                category: "Овощи"
            },
            {
                id: 5,
                src: "/static/images/twink.jpg",
                title: "Твинк",
                text: "Просто твинк",
                category: "Овощи"
            },
            {
                id: 6,
                src: "/static/images/tomatoes.jpg",
                title: "Помидоры",
                text: "Сочные помидоры",
                category: "Овощи"
            },
            // Фрукты
            {
                id: 7,
                src: "/static/images/oranges.jpg",
                title: "Апельсины",
                text: "Сладкие апельсины",
                category: "Фрукты"
            },
            {
                id: 8,
                src: "/static/images/bananas.jpg",
                title: "Бананы",
                text: "Спелые бананы",
                category: "Фрукты"
            },
            {
                id: 9,
                src: "/static/images/apples.jpg",
                title: "Яблоки",
                text: "Красные яблоки",
                category: "Фрукты"
            },
            {
                id: 10,
                src: "static/images/milk.jpg",
                title: "Молоко",
                text: "Молоко 3,2 %",
                category: "Молочные Продукты",
            },
            {
                id: 11,
                src: "static/images/cheese.jpg",
                title: "Сыр",
                text: "Сыр классический",
                category: "Молочные Продукты",
            },
            {
                id: 12,
                src: "static/images/butter.jpg",
                title: "Сливочное масло ",
                text: "Сливочное масло 5 %",
                category: "Молочные Продукты",
            }
        ]
    }

    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)

        const data = this.getData()
        data.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot)
            productCard.render(item, this.clickCard.bind(this))
        })
    }

    clickCard(e) {
        const cardId = e.target.dataset.id

        const productPage = new ProductPage(this.parent, cardId)
        productPage.render()
    }
}