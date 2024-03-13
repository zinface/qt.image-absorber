#include "clipboardimagesavework.h"
#include "clipboardmanager.h"
#include "global.h"

#include <QUuid>

ClipboardImageSaveWork::ClipboardImageSaveWork(ClipboardManager *parent)
    : QObject{}
    , manager(parent)
{

}

void ClipboardImageSaveWork::slotRequestPreviewImage(QPixmap image, QSize size)
{
    QPixmap pixmap = image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    emit manager->onRequestPreviewImage(pixmap);
}

void ClipboardImageSaveWork::slotRequestSaveImage(QPixmap image)
{
    auto size = image.size();
    QString uuid = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
    QString savePath = QString("%1/%2.png").arg(GL.storeDir()).arg(uuid);
    if (!savePath.isEmpty()) {
        image.save(savePath,"png");
    }
    emit manager->onRequestSaveImage();
}
