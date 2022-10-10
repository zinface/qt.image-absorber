
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    QString getStatus() const;
    void setStatus(const QString &value);

private:
    void updatePreviewImage(QSize size);

private:
    QClipboard *clipboard;
    Ui::MainWindow *ui;
    QPixmap hisImage;
    QLabel status;

    QDir h_absorber;
    bool mut;

public slots:
    void clipboardChanged();
    void on_chagneStorePath_triggered();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_onlyPreview_stateChanged(int arg1);
};

#endif // MAINWINDOW_H

