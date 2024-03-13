#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>



class Global
{
    Global();
public:
    static Global &instance();

    QString storeDir() const;
    void setStoreDir(const QString &newStoreDir);

private:
    QString m_storeDir;
};

#define GL Global::instance()

#endif // GLOBAL_H
