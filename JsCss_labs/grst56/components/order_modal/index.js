/**
 * Компонент модального окна заказа
 */
export class OrderModalComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return `
            <div class="modal fade" id="orderModal" tabindex="-1" aria-hidden="true">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title">Оформление заказа</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div class="modal-body">
                            <form id="orderForm">
                                <div class="mb-3">
                                    <label for="address" class="form-label">Адрес доставки</label>
                                    <input type="text" class="form-control" id="address" required>
                                </div>
                                <div class="mb-3">
                                    <label for="time" class="form-label">Время доставки</label>
                                    <select class="form-select" id="time" required>
                                        <option value="">Выберите время</option>
                                        <option value="6:00-9:00">С 6:00 до 9:00</option>
                                        <option value="10:00-12:00">С 10:00 до 12:00</option>
                                        <option value="12:00-14:00">С 12:00 до 14:00</option>
                                        <option value="14:00-17:00">С 14:00 до 17:00</option>
                                        <option value="17:00-21:00">С 17:00 до 21:00</option>
                                    </select>
                                </div>
                            </form>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отмена</button>
                            <button type="submit" form="orderForm" class="btn btn-primary">Оформить</button>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    render() {
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);
        
        document.getElementById('orderForm').addEventListener('submit', (e) => {
            e.preventDefault();
            const modal = bootstrap.Modal.getInstance(document.getElementById('orderModal'));
            modal.hide();
            
            // Показываем сообщение об успешном заказе
            alert('Вы успешно заказали продукт!');
        });
    }
}