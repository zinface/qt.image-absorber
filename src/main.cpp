
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>

void moveCenter(MainWindow &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("图片吸收器 - v0.1");
    MainWindow wm;
    wm.show();
   
    moveCenter(wm);

    return a.exec();
}
