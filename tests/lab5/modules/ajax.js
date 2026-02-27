class Ajax {
    /**
     * Выполняет GET-запрос
     * @param {string} url - URL для запроса
     * @param {function} callback - Функция обратного вызова (data, status)
     * @param {Object} [headers={}] - Дополнительные заголовки
     */
    get(url, callback, headers = {}) {
        const xhr = new XMLHttpRequest();
        xhr.open('GET', url, true);
        
        // Устанавливаем заголовки
        this._setHeaders(xhr, headers);
        
        xhr.send();

        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                this._handleResponse(xhr, callback);
            }
        };
    }

    /**
     * Выполняет POST-запрос
     * @param {string} url - URL для запроса
     * @param {Object} data - Данные для отправки
     * @param {function} callback - Функция обратного вызова (data, status)
     * @param {Object} [headers={}] - Дополнительные заголовки
     */
    post(url, data, callback, headers = {}) {
        const xhr = new XMLHttpRequest();
        xhr.open('POST', url, true);
        
        // Устанавливаем стандартные заголовки для JSON
        headers['Content-Type'] = 'application/json';
        this._setHeaders(xhr, headers);
        
        xhr.send(JSON.stringify(data));

        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                this._handleResponse(xhr, callback);
            }
        };
    }

    /**
     * Выполняет PUT-запрос
     * @param {string} url - URL для запроса
     * @param {Object} data - Данные для отправки
     * @param {function} callback - Функция обратного вызова (data, status)
     * @param {Object} [headers={}] - Дополнительные заголовки
     */
    put(url, data, callback, headers = {}) {
        const xhr = new XMLHttpRequest();
        xhr.open('PUT', url, true);
        
        headers['Content-Type'] = 'application/json';
        this._setHeaders(xhr, headers);
        
        xhr.send(JSON.stringify(data));

        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                this._handleResponse(xhr, callback);
            }
        };
    }

    /**
     * Выполняет DELETE-запрос
     * @param {string} url - URL для запроса
     * @param {function} callback - Функция обратного вызова (data, status)
     * @param {Object} [headers={}] - Дополнительные заголовки
     */
    delete(url, callback, headers = {}) {
        const xhr = new XMLHttpRequest();
        xhr.open('DELETE', url, true);

        headers['Content-Type'] = 'application/json';
        Object.keys(headers).forEach(key => {
            xhr.setRequestHeader(key, headers[key]);
        });
        
        xhr.onload = () => {
            try {
                const data = xhr.responseText ? JSON.parse(xhr.responseText) : null;
                callback(data, xhr.status);
            } catch (e) {
                callback(null, xhr.status);
            }
        };
        
        xhr.onerror = () => {
            callback(null, 0);
        };
        
        xhr.send();
    }

    /**
     * Устанавливает заголовки для запроса
     * @param {XMLHttpRequest} xhr - Объект запроса
     * @param {Object} headers - Объект с заголовками
     */
    _setHeaders(xhr, headers) {
        Object.keys(headers).forEach(key => {
            xhr.setRequestHeader(key, headers[key]);
        });
    }

    /**
     * Обрабатывает ответ сервера
     * @param {XMLHttpRequest} xhr - Объект запроса
     * @param {function} callback - Функция обратного вызова
     */
    _handleResponse(xhr, callback) {
        let data = null;
        try {
            data = xhr.responseText ? JSON.parse(xhr.responseText) : null;
        } catch (e) {
            console.error('Parsing error:', e);
        }
        callback(data, xhr.status);
    }
}

export const ajax = new Ajax();