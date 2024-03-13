
#include "global.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QMimeData>
#include <QStandardPaths>
#include <QTextStream>
#include <QUuid>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hpreview->addAction(ui->chagneStorePath);

    QDir(GL.storeDir()).mkpath(".");
    setWindowTitle("当前状态: 仅预览");
    ui->statusbar->showMessage(QString("存储位置: %1").arg(GL.storeDir()));

    // 剪贴板信号
    clipboard = qApp->clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, &MainWindow::slotClipboardDataChanged);

    manager = new ClipboardManager;
    manager->start();
    connect(manager, &ClipboardManager::onRequestPreviewImage, this, &MainWindow::slotOnRequestPreviewImage);
    connect(manager, &ClipboardManager::onRequestSaveImage, this, &MainWindow::slotOnRequestSaveImage);

}
MainWindow::~MainWindow()
{

}

void MainWindow::slotClipboardDataChanged()
{
    // 查看剪切版中是否有图片信息
    const QMimeData *mime = clipboard->mimeData();
    if (mime->hasImage()) {

        m_etimer.restart();
        QPixmap pixmap = qvariant_cast<QPixmap>(mime->imageData());

        if (pixmap.isNull()) {
            ui->statusbar->showMessage("空的！");
            return;
        }

        if (pixmap.toImage() == hisImage.toImage()) {
            ui->statusbar->showMessage("相同的！");
            return;
        }

        hisImage = pixmap;
        if (ui->onlyPreview->isChecked() == true) {
            emit manager->requestPreviewImage(hisImage, ui->hpreview->size());
        } else {
            if (ui->noPreview->isChecked() == false) {
                emit manager->requestPreviewImage(hisImage, ui->hpreview->size());
            }
            emit manager->requestSaveImage(hisImage);
        }

        return;
    }
}

void MainWindow::slotOnRequestPreviewImage(QPixmap pixmap)
{
    ui->hpreview->setPixmap(pixmap);

    QString str = QString("本次消耗: %1 ms").arg(m_etimer.elapsed());
    qDebug() << str;

    ui->statusbar->showMessage(str);
}

void MainWindow::slotOnRequestSaveImage()
{
    QString str = QString("本次消耗: %1 ms").arg(m_etimer.elapsed());
    qDebug() << str;

    ui->statusbar->showMessage(str);
}

void MainWindow::updatePreviewImage(QSize size)
{
    int w = size.width();
    int h = size.height();

    if (hisImage.isNull()) {
        return;
    }

    m_etimer.restart();

    QPixmap temp;
    bool doScale = false;
    if (hisImage.width() > w || hisImage.height() > h) {
        emit manager->requestPreviewImage(hisImage, ui->hpreview->size());
    } else {
        temp = hisImage;
    }
    ui->hpreview->setPixmap(temp);
}

void MainWindow::on_chagneStorePath_triggered()
{
    qDebug() << __FUNCTION__;
    QString dir = QFileDialog::getExistingDirectory(this, tr("存储位置"), GL.storeDir(),
                                                    QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        GL.setStoreDir(dir);
        ui->statusbar->showMessage(QString("存储位置: %1").arg(dir));
    }
}

void MainWindow::on_onlyPreview_stateChanged(int arg1)
{
    if (ui->onlyPreview->isChecked()) {
        setWindowTitle("当前状态: 仅预览");
    } else {
        setWindowTitle(QString("存储位置: %1").arg(GL.storeDir()));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updatePreviewImage(event->size());
}
