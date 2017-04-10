#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Qt::WindowFlags flags = w.windowFlags();
    w.setWindowFlags(flags | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    w.show();

    return a.exec();
}
