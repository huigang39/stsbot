#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locate.h"
#include "eForm.h"

// 调用摄像头
#include <QCameraInfo>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QPixmap>
// 弹窗
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("导航界面");

    // 获取可用摄像头设备并输出在控制台
    QList<QCameraInfo> infos = QCameraInfo::availableCameras();
    qDebug() << infos.value(0).deviceName() << ":" << infos.value(0).description();
    QString camera = infos.value(0).deviceName();
    qDebug() << camera;
    // 显示摄像头
    ca = new QCamera(camera.toUtf8(), this);
    ui->camera->show();

    QCameraViewfinder *v2 = new QCameraViewfinder(ui->camera);
    v2->resize(ui->camera->size());
    ca->setViewfinder(v2);
    v2->show();
    ca->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_guidButton_clicked()
{
}

void MainWindow::on_view_clicked()
{
    locate *loc = new locate;
    this->close();
    loc->show();
}

void MainWindow::on_view_2_clicked()
{
    eForm *e = new eForm();
    this->close();
    e->show();
}
