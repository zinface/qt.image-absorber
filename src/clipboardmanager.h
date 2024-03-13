#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QThread>
#include <QWidget>

class ClipboardManager : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardManager(QObject *parent = nullptr);
    void start();
    void stop();

signals:
    void requestPreviewImage(QPixmap image, QSize size);
    void onRequestPreviewImage(QPixmap pixmap);

    void requestSaveImage(QPixmap image);
    void onRequestSaveImage();

private:
    QThread m_thread;

};

#endif // CLIPBOARDMANAGER_H
