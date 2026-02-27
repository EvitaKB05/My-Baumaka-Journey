import { MainPage } from './pages/main/index.js';

const app = document.getElementById('app');
const mainPage = new MainPage(app);
mainPage.render();