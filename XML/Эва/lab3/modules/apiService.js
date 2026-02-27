import { ajax } from './ajax.js';
import { productUrls } from './productUrls.js';

export class ApiService {
    /**
     * Получить список всех продуктов
     * @param {function} callback - Функция обратного вызова
     */
    static getProducts(callback) {
        ajax.get(productUrls.getProducts(), callback);
    }

    /**
     * Получить продукт по ID
     * @param {number} id - ID продукта
     * @param {function} callback - Функция обратного вызова
     */
    static getProduct(id, callback) {
        ajax.get(productUrls.getProductById(id), callback);
    }

    /**
     * Создать новый продукт
     * @param {object} productData - Данные продукта
     * @param {function} callback - Функция обратного вызова
     */
    static createProduct(productData, callback) {
        ajax.post(productUrls.createProduct(), productData, callback);
    }
}