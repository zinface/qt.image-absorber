#include "global.h"

#include <QStandardPaths>

Global::Global()
{
    m_storeDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/image-absorber";
}

Global &Global::instance()
{
    static Global global;
    return global;
}

QString Global::storeDir() const
{
    return m_storeDir;
}

void Global::setStoreDir(const QString &newStoreDir)
{
    m_storeDir = newStoreDir;
}
