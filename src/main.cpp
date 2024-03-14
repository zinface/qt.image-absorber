
#include "mainwindow.h"

#include <QApplication>
#include <QCursor>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QPoint>
#include <QScreen>

void moveCenter(QWidget &wm) {
    QScreen *screen = QApplication::screenAt(QCursor::pos());
    auto desktop = screen->geometry();
    auto afterX = (desktop.width() - wm.width()) / 2;
    auto afterY = (desktop.height() - wm.height()) /2;

    wm.move(afterX + desktop.x(), afterY + desktop.y());

    qDebug() << screen->availableGeometry();
    qDebug() << screen->geometry();
    qDebug() << QCursor::pos();
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
