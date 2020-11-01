#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix("Qt.png");
    QSplashScreen splash(pix);
    splash.show();
    a.processEvents();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
