#include "clipboardmanager.h"
#include "clipboardimagesavework.h"

ClipboardManager::ClipboardManager(QObject *parent)
    : QObject{parent}
{

}

void ClipboardManager::start()
{
    stop();

    ClipboardImageSaveWork *worker = new ClipboardImageSaveWork(this);
    worker->moveToThread(&m_thread);
    connect(this, &ClipboardManager::requestPreviewImage, worker, &ClipboardImageSaveWork::slotRequestPreviewImage);
    connect(this, &ClipboardManager::requestSaveImage, worker, &ClipboardImageSaveWork::slotRequestSaveImage);
    connect(&m_thread, &QThread::finished, worker, &ClipboardImageSaveWork::deleteLater);
    m_thread.start();
}

void ClipboardManager::stop()
{
    if (m_thread.isRunning()) {
        m_thread.quit();
        m_thread.wait();
    }
}
