#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Configuración del estilo de la aplicación
    app.setStyle("Fusion");

    // Configurar tema y paleta de colores
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240, 240, 240));
    palette.setColor(QPalette::WindowText, QColor(50, 50, 50));
    palette.setColor(QPalette::Base, QColor(255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    palette.setColor(QPalette::Button, QColor(240, 240, 240));
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    app.setPalette(palette);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}