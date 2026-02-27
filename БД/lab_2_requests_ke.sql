select * from customers;
select idcustomer from customers;
select * from orders;
select * from products;



select * from items;
delete from items;
delete from orders;
delete from customers;
delete from products;

ALTER TABLE customers ADD age NUMERIC;
UPDATE customers SET age = vals.age FROM (VALUES(64,19), (65, 23),(66, 28), (67, 33), (68, 38), (69, 43), (70, 48), (71, 53), (72, 58), (73, 63), (74, 68), (75, 73), (76, 78)) 
AS vals(id_cust, age) WHERE customers.id_customer = vals.id_cust;



DELETE FROM items WHERE total = 99.99;

INSERT INTO customers (companyname, lastname, firstname, address, city, indexcode, phone, email) VALUES
('RobotLabs', 'Петров', 'Иван', 'Улица Кирова, 25', 'Санкт-Петербург', '191186', '+7 812 456-78-90', 'i.petrov@robotlabs.ru'),
('QuantumLeap', 'Сидорова', 'Мария', 'Улица Некрасова, 50', 'Москва', '117105', '+7 495 987-65-43', 'm.sidorova@quantumleap.com'),
('NanoTech', 'Кузнецов', 'Дмитрий', 'Улица Советская, 1', 'Новосибирск', '630099', '+7 913 765-43-21', 'd.kuznetsov@nanotech.net'),
('Cyberdyne', 'Смирнова', 'Елена', 'Улица Гагарина, 12', 'Екатеринбург', '620026', '+7 922 109-87-65', 'e.smirnova@cyberdyne.org'),
('StarLabs', 'Васильев', 'Андрей', 'Улица Мира, 3', 'Казань', '420111', '+7 8552 258-09-76', 'a.vasiliev@starlabs.biz'),
('FutureTech', 'Попова', 'Ольга', 'Улица Декабристов, 45', 'Нижний Новгород', '603089', '+7 8312 417-29-58', 'o.popova@futuretech.info'),
('InnovateInc', 'Соколов', 'Сергей', 'Улица Карла Маркса, 7', 'Самара', '443010', '+7 846 632-85-14', 's.sokolov@innovateinc.co'),
('TechSphere', 'Морозова', 'Татьяна', 'Улица Кирова, 9', 'Омск', '644099', '+7 904 564-97-32', 't.morozova@techsphere.ca'),
('GlobalTech', 'Волков', 'Александр', 'Улица Фрунзе, 11', 'Челябинск', '454080', '+7 951 789-01-23', 'a.volkov@globaltech.de'),
('ApexTech', 'Новикова', 'Анна', 'Улица Горького, 13', 'Ростов-на-Дону', '344019', '+7 863 201-34-56', 'a.novikova@apextech.fr'),
('ZenithTech', 'Козлов', 'Михаил', 'Улица Пушкина, 15', 'Уфа', '450000', '+7 937 852-96-34', 'm.kozlov@zenithtech.it'),
('NovaTech', 'Иванова', 'Наталья', 'Улица Ленина, 17', 'Пермь', '614045', '+7 902 123-78-90', 'n.ivanova@novatech.es'),
('PinnacleTech', 'Смирнов', 'Владимир', 'Улица Советская, 19', 'Волгоград', '400131', '+7 961 987-01-23', 'v.smirnov@pinnacle.jp');

INSERT INTO products (productname, productprice, instock, reorder, description) VALUES
('Ноутбук Модель X', 65000, 35, TRUE, 'Мощный ноутбук для работы и игр'),
('Смартфон Z10', 32000, 52, TRUE, 'Современный смартфон с отличной камерой'),
('Планшет TabPro', 18500, 27, FALSE, 'Удобный планшет для чтения и просмотра видео'),
('Наушники беспроводные SoundMax', 4500, 88, TRUE, 'Наушники с шумоподавлением'),
('Смарт-часы WatchFit', 7900, 61, TRUE, 'Смарт-часы с функцией отслеживания активности'),
('Клавиатура беспроводная KeyMaster', 3100, 43, FALSE, 'Эргономичная клавиатура для комфортной работы'),
('Мышь беспроводная MousePro', 1200, 95, TRUE, 'Точная мышь для работы и игр'),
('Внешний жесткий диск 2TB', 5800, 30, TRUE, 'Портативный жесткий диск для хранения данных'),
('Флешка USB 128GB', 800, 120, FALSE, 'Быстрая флешка с большим объемом памяти'),
('Веб-камера CamVision', 2300, 70, TRUE, 'Веб-камера высокого разрешения'),
('Принтер PrintMaster', 9500, 15, TRUE, 'Беспроводной принтер для дома и офиса'),
('Монитор DisplayPro 24"', 14000, 22, FALSE, 'Монитор с диагональю 24 дюйма'),
('Игровая мышь GameMouse', 3800, 48, TRUE, 'Игровая мышь с высокой точностью');


INSERT INTO orders (idcustomer, orderdate, shipdate, paiddate, status) VALUES
(64, '2024-01-05', '2024-01-07', '2024-01-05', 'C'),
(65, '2024-01-06', '2024-01-08', '2024-01-06', 'P'),
(66, '2024-01-07', '2024-01-09', '2024-01-07', 'A'),
(67, '2024-01-08', '2024-01-10', '2024-01-08', 'C'),
(68, '2024-01-09', '2024-01-11', '2024-01-09', 'P'),
(69, '2024-01-10', '2024-01-12', '2024-01-10', 'A'),
(70, '2024-01-11', '2024-01-13', '2024-01-11', 'C'),
(71, '2024-01-12', '2024-01-14', '2024-01-12', 'P'),
(72, '2024-01-13', '2024-01-15', '2024-01-13', 'A'),
(73, '2024-01-14', '2024-01-16', '2024-01-14', 'C'),
(74, '2024-01-15', '2024-01-17', '2024-01-15', 'P'),
(75, '2024-01-16', '2024-01-18', '2024-01-16', 'A'),
(76, '2024-01-17', '2024-01-19', '2024-01-17', 'C');
UPDATE customers SET city = 'Москва' WHERE city = 'Казань';
UPDATE orders SET ship_date = NULL  WHERE ship_date = '2024-01-13';
UPDATE customers SET address = 'Улица Пушкина, 15' WHERE address = 'Улица Мира, 3';
UPDATE customers SET address = 'Улица Горького, 13' WHERE address = 'Улица Некрасова, 50';
UPDATE customers SET address = 'Улица Гагарина, 12' WHERE address = 'Улица Фрунзе, 11';
UPDATE orders SET paid_date = NULL WHERE paid_date = '2024-01-10';
UPDATE orders SET paid_date = NULL WHERE paid_date = '2024-01-16';
UPDATE orders SET paid_date = NULL WHERE paid_date = '2024-01-05';
UPDATE orders SET paid_date = NULL WHERE paid_date = '2024-01-08';
INSERT INTO items (idproduct, idorder, quantity, total) VALUES
(47, 154, 2, 1599.98),
(48, 155, 1, 299.99),
(49, 156, 3, 449.97),
(50, 157, 1, 499.99),
(51, 158, 2, 399.98),
(52, 159, 1, 99.99),
(53, 160, 5, 249.95),
(54, 161, 1, 79.99),
(55, 162, 10, 199.90),
(56, 163, 2, 119.98),
(57, 164, 1, 149.99),
(58, 165, 1, 249.99),
(59, 166, 1, 799.99);

/*CREATE TABLE IF NOT EXISTS customers (
 id_customer INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
 company_name VARCHAR(),
 lastname VARCHAR() NOT NULL,
 firstname VARCHAR()NOT NULL,
 address VARCHAR() NOT NULL,
 city VARCHAR() NOT NULL,
 index_code INT NOT NULL,
 phone VARCHAR(20) NOT NULL,
 email VARCHAR() NOT NULL
);

CREATE TABLE IF NOT EXISTS orders (
 id_order INT PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
 id_customer INT NOT NULL,
 order_date DATE NOT NULL,
 ship_date DATE,
 paid_date DATE,
 status VARCHAR(3) NOT NULL,
);
*/

UPDATE customers SET company_name = 'Amor' WHERE company_name = 'NovaTech';

/* ЗАПРОСЫ КУДАБАЕВА ИУ5-42Б */

/* 1 - ALL TABLES */
SELECT * FROM customers;
SELECT * FROM orders;
SELECT * FROM items;
SELECT * FROM products;

/* 2 - SOME COLUMNS FROM TABLES */
SELECT company_name, lastname, firstname, age FROM customers;
/* 3 - SORT */
SELECT lastname, firstname, age FROM customers ORDER BY age; /* growth */
SELECT lastname, firstname, age FROM customers ORDER BY age DESC; /* decrease */
/* 4 - LIMIT */
SELECT product_name, product_price, description FROM products LIMIT 5;
/* 5 - COMPARE */
SELECT * FROM customers WHERE city = 'Москва';
/* 6 - BETWEEN */
SELECT * FROM products WHERE product_price BETWEEN 5000 AND 20000;
/* 7 - IN and SUB QUEST */
SELECT id_customer, lastname, firstname FROM customers WHERE id_customer IN (SELECT id_customer FROM orders WHERE status = 'A');
/* 8 - LIKE + STRINGS */
SELECT LOWER(company_name), CONCAT(lastname,' ', firstname) AS FIO FROM customers WHERE company_name LIKE 'A%'; 
/* 9 -  IS NULL */
SELECT * FROM orders WHERE ship_date IS NULL;
/* 10 - AGR FUNC */
SELECT orders.status, SUM(total) AS total_stats FROM ITEMS JOIN orders ON items.id_order=orders.id_order GROUP BY  orders.status;
/* 11 - AGR + HAVING */
SELECT CONCAT(lastname,' ', firstname) AS FIO, SUM(total) AS total_stats FROM ITEMS JOIN orders ON items.id_order =orders.id_order 
JOIN customers ON orders.id_customer = customers.id_customer GROUP BY FIO
HAVING SUM(total)>300 
ORDER BY FIO; 
/* 12 - NEXT TABLE DATA */
SELECT 
customers.id_customer,
CONCAT(customers.lastname,' ', customers.firstname) AS FIO,
SUM(items.total) AS total_stats, items.quantity, products.product_name, products.product_price
FROM orders 
JOIN customers ON orders.id_customer = customers.id_customer
JOIN items ON orders.id_order=items.id_order
JOIN products ON items.id_product=products.id_product 
GROUP BY customers.id_customer, items.quantity, products.product_name, products.product_price;
/* 13 - DISTINCT */
SELECT DISTINCT address FROM customers ;
/* 14 - EXIST */
SELECT id_product, product_name  FROM products
WHERE EXISTS (SELECT id_product FROM items WHERE items.id_product = products.id_product AND quantity > 4);
/* 15 - CASE */
SELECT  
CONCAT(customers.lastname,' ', customers.firstname) AS FIO, orders.status, 
CASE
	WHEN orders.status = 'C'  THEN 'Заказ отменён'
	WHEN orders.status = 'A' THEN 'Заказ выполнен'
	ELSE 'Заказ в пути'
END AS STATUS
FROM customers JOIN orders ON orders.id_customer = customers.id_customer;

/* Вариант 10 */

/*1 - Получить информацию о заказе: id заказа, фамилию, имя, адрес, 
дата заказа, дата отправки. Список отсортировать так, чтоб 
заказы, отправленные раньше, выводились в конце. */

SELECT 
id_order,
CONCAT(customers.lastname,' ', customers.firstname) AS FIO,
customers.address,
order_date,
ship_date
FROM orders 
JOIN customers ON orders.id_customer = customers.id_customer
ORDER BY ship_date  DESC;

/*2 - Получить  информацию  о  покупателях  (фамилия,  имя,  адрес, 
телефон), которые оплатили заказ.  Список отсортировать по 
фамилиям.  */

SELECT 
id_order,
CONCAT(customers.lastname,' ', customers.firstname) AS FIO,
customers.address,
customers.phone
FROM orders
JOIN customers ON orders.id_customer = customers.id_customer
WHERE paid_date  IS NOT NULL
ORDER BY id_order;