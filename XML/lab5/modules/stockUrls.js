class StockUrls {
    constructor() {
        this.baseUrl = 'http://localhost:3000';
    }

    getStocks() {
        return `${this.baseUrl}/cats`;
    }

    getStockById(id) {
        return `${this.baseUrl}/cats/${id}`;
    }

    createStock() {
        return `${this.baseUrl}/cats`;
    }

    removeStockById(id) {
        return `${this.baseUrl}/cats/${id}`;
    }

    updateStockById(id) {
        return `${this.baseUrl}/cats/${id}`;
    }

    getCatImage(imageName) {
        return `${this.baseUrl}/cats-images/${imageName}.jpg`;
    }
}

export const stockUrls = new StockUrls();