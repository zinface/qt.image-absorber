#ifndef CLIPBOARDIMAGESAVEWORK_H
#define CLIPBOARDIMAGESAVEWORK_H

#include "clipboardmanager.h"
#include <QImage>
#include <QObject>
#include <QWidget>

class ClipboardImageSaveWork : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardImageSaveWork(ClipboardManager *parent = nullptr);

public slots:
    void slotRequestPreviewImage(QPixmap image, QSize size);
    void slotRequestSaveImage(QPixmap image);

private:
    ClipboardManager *manager;
};

#endif // CLIPBOARDIMAGESAVEWORK_H
