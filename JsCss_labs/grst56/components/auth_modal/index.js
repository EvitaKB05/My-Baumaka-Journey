/**
 * Компонент модального окна авторизации
 */
export class AuthModalComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return `
            <div class="modal fade" id="authModal" tabindex="-1" aria-hidden="true">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title">Вход / Регистрация</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div class="modal-body">
                            <form id="authForm">
                                <div class="mb-3">
                                    <label for="email" class="form-label">Email</label>
                                    <input type="email" class="form-control" id="email" required>
                                </div>
                                <div class="mb-3">
                                    <label for="password" class="form-label">Пароль</label>
                                    <input type="password" class="form-control" id="password" required>
                                </div>
                            </form>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отмена</button>
                            <button type="submit" form="authForm" class="btn btn-primary">Войти</button>
                        </div>
                    </div>
                </div>
            </div>
        `;
    }

    render() {
        const html = this.getHTML();
        this.parent.insertAdjacentHTML('beforeend', html);
        
        document.getElementById('authForm').addEventListener('submit', (e) => {
            e.preventDefault();
            alert('Вы успешно авторизованы!');
            const modal = bootstrap.Modal.getInstance(document.getElementById('authModal'));
            modal.hide();
        });
    }
}