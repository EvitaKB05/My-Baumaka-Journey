import { ProductComponent } from "../../components/product/index.js"
import { BackButtonComponent } from "../../components/back_button/index.js"
import { MainPage } from "../main/index.js"
import { BadgesComponent } from "../../components/badges/index.js"

export class ProductPage {
    constructor(parent, id) {
        this.parent = parent
        this.id = id
    }

    getData() {
        const allProducts = [
            // Мясо
            {
                id: 1,
                src: "static/images/beef.jpg",
                title: "Говядина",
                text: "Свежая говядина высшего качества. Идеально подходит для стейков и гуляша.",
                category: "Мясо",
                price: "500 руб/кг"
            },
            {
                id: 2,
                src: "static/images/lamb.jpg",
                title: "Баранина",
                text: "Нежная баранина. Отлично подходит для плова и шашлыка.",
                category: "Мясо",
                price: "600 руб/кг"
            },
            {
                id: 3,
                src: "static/images/chicken.jpg",
                title: "Курица",
                text: "Куриные грудки. Диетический продукт с высоким содержанием белка.",
                category: "Мясо",
                price: "300 руб/кг"
            },
            // Овощи
            {
                id: 4,
                src: "static/images/carrots.jpg",
                title: "Морковь",
                text: "Свежая морковь. Богата витамином А и клетчаткой.",
                category: "Овощи",
                price: "50 руб/кг"
            },
            {
                id: 5,
                src: "static/images/twink.jpg",
                title: "Главный овощ",
                text: "Rust'ер и этим всё сказано, никогда не трезв, любит пиво и носить чулки",
                category: "Овощи",
                price: "50 руб/кг (торг уместен)"
            },
            {
                id: 6,
                src: "static/images/tomatoes.jpg",
                title: "Помидоры",
                text: "Сочные помидоры. Содержат ликопин - мощный антиоксидант.",
                category: "Овощи",
                price: "150 руб/кг"
            },
            // Фрукты
            {
                id: 7,
                src: "static/images/oranges.jpg",
                title: "Апельсины",
                text: "Сладкие апельсины. Богаты витамином С.",
                category: "Фрукты",
                price: "120 руб/кг"
            },
            {
                id: 8,
                src: "static/images/bananas.jpg",
                title: "Бананы",
                text: "Спелые бананы. Отличный источник калия и энергии.",
                category: "Фрукты",
                price: "80 руб/кг"
            },
            {
                id: 9,
                src: "static/images/apples.jpg",
                title: "Яблоки",
                text: "Красные яблоки. Содержат пектин и множество витаминов.",
                category: "Фрукты",
                price: "90 руб/кг"
            },
            {
                id: 10,
                src: "static/images/milk.jpg",
                title: "Молоко 3,2 %",
                text: "Полезный и природный продукт.",
                category: "Молочные Продукты",
                price: "100 руб/л"
            },
            {
                id: 11,
                src: "static/images/cheese.jpg",
                title: "Сыр классический",
                text: "Любимец мышек и британцев.",
                category: "Молочные Продукты",
                price: "200 руб/100 г"
            },
            {
                id: 12,
                src: "static/images/.jpg",
                title: "Сливочное масло 5 %",
                text: "Очень нужный товарищ для вкусняшек.",
                category: "Молочные Продукты",
                price: "250 руб/100 г"
            }
        ];

        return allProducts.find(item => item.id === parseInt(this.id));
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <div id="product-page"></div>
            `
        )
    }

    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }

    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
    
        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
    
        const data = this.getData()
        const product = new ProductComponent(this.pageRoot)
        product.render(data)

        // Добавляем значок категории на страницу продукта
        const badgeContainer = document.createElement('div')
        this.pageRoot.appendChild(badgeContainer)
        const badge = new BadgesComponent(badgeContainer)
        badge.render(data.category)
        
        // Добавляем цену
        const priceElement = document.createElement('p')
        priceElement.className = 'mt-3'
        priceElement.innerHTML = `<strong>Цена:</strong> ${data.price}`
        this.pageRoot.appendChild(priceElement)
    }
}