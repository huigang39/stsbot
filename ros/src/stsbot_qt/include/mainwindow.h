#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// 摄像头
#include <QCameraImageCapture>
#include <QCamera>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_guidButton_clicked();

    void on_view_clicked();

    void on_view_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_forwardButton_clicked();

    void on_backButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    // 创建两个摄像头对象
    QCamera *ca;
    QCameraImageCapture *capture;
    QSerialPort *serialport;
};
#endif // MAINWINDOW_H
