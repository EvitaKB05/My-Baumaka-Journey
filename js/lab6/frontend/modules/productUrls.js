class ProductUrls {
    constructor() {
        this.baseUrl = 'http://localhost:3000';
    }

    getProducts() {
        return `${this.baseUrl}/products`;
    }

    getCategories() {
        return `${this.baseUrl}/categories`;
    }

    getProduct(id) {
        return `${this.baseUrl}/products/${id}`;
    }

    createProduct() {
        return `${this.baseUrl}/products`;
    }

    updateProduct(id) {
        return `${this.baseUrl}/products/${id}`;
    }

    deleteProduct(id) {
        return `${this.baseUrl}/products/${id}`;
    }
}

export const productUrls = new ProductUrls();