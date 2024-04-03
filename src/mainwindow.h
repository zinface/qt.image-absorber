
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clipboardmanager.h"

#include <QClipboard>
#include <QDir>
#include <QLabel>
#include <QMainWindow>
#include <QResizeEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updatePreviewImage(QSize size);

private:
    QClipboard *clipboard;
    Ui::MainWindow *ui;

    QPixmap hisImage;

    ClipboardManager *manager;
    QElapsedTimer m_etimer;

public slots:
    void slotClipboardDataChanged();
    void slotOnRequestPreviewImage(QPixmap pixmap);
    void slotOnRequestSaveImage();
    void on_chagneStorePath_triggered();
    void on_actionCopyOriginPixmap_triggered();
    void on_onlyPreview_stateChanged(int arg1);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // MAINWINDOW_H

