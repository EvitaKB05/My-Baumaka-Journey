import { MainPage } from "./pages/main/index.js";

/**
 * Точка входа в приложение
 */
class App {
    static init() {
        const appContainer = document.getElementById('app');
        const mainPage = new MainPage(appContainer);
        mainPage.render();
    }
}

App.init();