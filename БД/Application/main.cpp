#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Настройка стиля приложения
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Настройка палитры для темной темы (опционально)
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);

    // Загрузка настроек приложения
    QSettings settings("ArtSchool", "HousingManager");

    // Инициализация и отображение главного окна
    MainWindow w;

    // Восстановление размеров и позиции окна из настроек
    QRect defaultRect(100, 100, 800, 600);
    w.setGeometry(settings.value("mainWindowGeometry", defaultRect).toRect());

    // Проверка соединения с БД при старте (опционально)
    if (settings.value("autoConnect", false).toBool()) {
        QMetaObject::invokeMethod(&w, "dbconnect", Qt::QueuedConnection);
    }

    w.show();

    // Сохранение геометрии при закрытии
    QObject::connect(&a, &QApplication::aboutToQuit, [&]() {
        settings.setValue("mainWindowGeometry", w.geometry());
    });

    return a.exec();
}
