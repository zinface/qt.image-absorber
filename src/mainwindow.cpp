
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QMimeData>
#include <QStandardPaths>
#include <QTextStream>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , h_absorber(QStandardPaths::locate(QStandardPaths::PicturesLocation, QString(), QStandardPaths::LocateDirectory) + "image-absorber")
  , mut(false)
{
    ui->setupUi(this);
    ui->statusbar->addWidget(&status);
    ui->hpreview->addAction(ui->chagneStorePath);
    status.setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);

// 存储位置
    h_absorber.mkdir(h_absorber.path());
    setStatus("存储位置: " + h_absorber.path()+"\n"+"当前状态: 仅预览");

    clipboard = qApp->clipboard();  // 开始监控程序
    connect(clipboard, &QClipboard::changed, this, &MainWindow::clipboardChanged);
}
MainWindow::~MainWindow()
{

}

QString MainWindow::getStatus() const
{
    return status.text();
}

void MainWindow::setStatus(const QString &value)
{
    status.setText(value);
}

void MainWindow::clipboardChanged()
{
    // 查看剪切版中是否有图片信息
    const QMimeData *mime= clipboard->mimeData();
    if (mime->hasImage()) {
        // 从剪切板中取出一张图
        QImage image = clipboard->image();

        // 存储为缓冲
        QByteArray imageData;
        QBuffer buffer(&imageData);
        image.save(&buffer, "png");

        // 历史图缓冲
        QByteArray m_imageData;
        QBuffer m_buffer(&m_imageData);
        hisImage.save(&m_buffer, "png");

        // 比较一次，如果与历史相同将直接跳过
        if (m_imageData.compare(imageData) == 0) {
            return;
        }

        // 存储到历史
        hisImage = QPixmap::fromImage(image);
        // 显示到预览
        ui->hpreview->setPixmap(hisImage.scaled(ui->hpreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    updatePreviewImage(this->size());

    if (mime->hasImage() && !ui->onlyPreview->isChecked()) {
        show();
        QString uuid = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
        QString savePath = QString("%1/%2.png").arg(h_absorber.path()).arg(uuid);
        if (mut == true) return;
        mut = true;

//        savePath = QFileDialog::getSaveFileName(this,"存储为", savePath,"png files (*.png);;all files(*.*)");
        qDebug() << savePath;
        if (!savePath.isEmpty()) {
            hisImage.save(savePath,"png");
        }
        mut = false;
    } else {
        setStatus("当前状态: 仅预览");
    }
}

void MainWindow::updatePreviewImage(QSize size)
{
    int w = size.width();
    int h = size.height();

    ui->hpreview->setMinimumSize(10, 10);
    QPixmap imagePixmap = hisImage;
    if (imagePixmap.isNull()) {
        return;
    }

    QPixmap temp;
    bool doScale = false;
    if (imagePixmap.width() > w || imagePixmap.height() > h) {
        temp = imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        temp = imagePixmap;
    }
    ui->hpreview->setPixmap(temp);
}

void MainWindow::on_chagneStorePath_triggered()
{
    qDebug() << __FUNCTION__;
    QString dir = QFileDialog::getExistingDirectory(this, tr("存储位置"),
                                                    h_absorber.path(),
                                                    QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        h_absorber.setPath(dir);
        setStatus(QString("存储位置: %1").arg(dir));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updatePreviewImage(event->size());
}

void MainWindow::on_onlyPreview_stateChanged(int arg1)
{
    if (ui->onlyPreview->isChecked()) {
        setStatus("当前状态: 仅预览");
    } else {
        setStatus(QString("存储位置: %1").arg(h_absorber.path()));
    }
}
