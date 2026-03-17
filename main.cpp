#include <QApplication>
#include <QFont>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Abilita high-DPI su Qt6 (default ON, ma lo esplicitiamo)
    QApplication app(argc, argv);
    app.setApplicationName("Symbol Picker");
    app.setApplicationVersion("1.0");

    // Font di default leggibile
    QFont font = app.font();
    font.setFamily("Noto Sans");
    font.setPixelSize(13);
    app.setFont(font);

    MainWindow w;
    w.show();
    return app.exec();
}
