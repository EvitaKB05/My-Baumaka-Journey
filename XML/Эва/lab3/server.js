const express = require('express');
const cors = require('cors');
const app = express();
const port = 3000;

// Включаем CORS
app.use(cors());

// Mock данные для продуктов
let products = [
  // Мясо
  { id: 1, title: "Говядина", text: "Свежая говядина", category: "Мясо", price: "500 руб/кг", src: "static/images/beef.jpg" },
  { id: 2, title: "Баранина", text: "Нежная баранина", category: "Мясо", price: "600 руб/кг", src: "static/images/lamb.jpg" },
  { id: 3, title: "Курица", text: "Куриные грудки", category: "Мясо", price: "300 руб/кг", src: "static/images/chicken.jpg" },
  
  // Овощи
  { id: 4, title: "Морковь", text: "Свежая морковь", category: "Овощи", price: "50 руб/кг", src: "static/images/carrots.jpg" },
  { id: 5, title: "Твинк", text: "Rust'ер и этим всё сказано", category: "Овощи", price: "50 руб/кг", src: "static/images/twink.jpg" },
  { id: 6, title: "Помидоры", text: "Сочные помидоры", category: "Овощи", price: "150 руб/кг", src: "static/images/tomatoes.jpg" },
  
  // Фрукты
  { id: 7, title: "Апельсины", text: "Сладкие апельсины", category: "Фрукты", price: "120 руб/кг", src: "static/images/oranges.jpg" },
  { id: 8, title: "Бананы", text: "Спелые бананы", category: "Фрукты", price: "80 руб/кг", src: "static/images/bananas.jpg" },
  { id: 9, title: "Яблоки", text: "Красные яблоки", category: "Фрукты", price: "90 руб/кг", src: "static/images/apples.jpg" },
  
  // Молочные продукты
  { id: 10, title: "Молоко", text: "Молоко 3,2%", category: "Молочные Продукты", price: "100 руб/л", src: "static/images/milk.jpg" },
  { id: 11, title: "Сыр", text: "Классический сыр", category: "Молочные Продукты", price: "200 руб/100г", src: "static/images/cheese.jpg" },
  { id: 12, title: "Масло", text: "Сливочное масло", category: "Молочные Продукты", price: "250 руб/100г", src: "static/images/butter.jpg" }
];

// Роут для получения всех продуктов
app.get('/products', (req, res) => {
  res.json(products);
});

// Роут для создания продукта
app.post('/products', express.json(), (req, res) => {
  const newProduct = { ...req.body, id: products.length + 1 };
  products.push(newProduct);
  res.status(201).json(newProduct);
});

// Запуск сервера
app.listen(port, () => {
  console.log(`Сервер API запущен на http://localhost:${port}`);
});