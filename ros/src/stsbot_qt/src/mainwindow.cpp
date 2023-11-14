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
#include <QDebug>
// 弹窗
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("导航界面");

    // 获取可用摄像头设备并输出在控制台
    QList<QCameraInfo> infos = QCameraInfo::availableCameras();
    QStringList serialNamePort;
    serialport = new QSerialPort(this);
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
    foreach (const QSerialPortInfo &inf0, QSerialPortInfo::availablePorts())
    {
        serialNamePort << inf0.portName();
    }
    ui->serialBox->addItems(serialNamePort);
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

void MainWindow::on_pushButton_clicked()
{
    serialport->setPortName(ui->serialBox->currentText());
    serialport->setBaudRate(ui->baudrateBox->currentText().toInt());
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setStopBits(QSerialPort::OneStop);
    serialport->setParity(QSerialPort::NoParity);
    if (true == serialport->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, "提示", "已成功连接电机");
    }
    else
    {
        QMessageBox::critical(this, "提示", "连接电机失败");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    serialport->close();
    QMessageBox::information(this, "提示", "已断开连接！");
}

void MainWindow::on_forwardButton_clicked()
{
    serialport->write("W");
    qDebug("W\n");
}

void MainWindow::on_backButton_clicked()
{
    serialport->write("B");
    qDebug("B\n");
}

void MainWindow::on_leftButton_clicked()
{
    serialport->write("E");
    qDebug("E\n");
}

void MainWindow::on_rightButton_clicked()
{
    serialport->write("R");
    qDebug("R\n");
}

void MainWindow::on_pushButton_3_clicked()
{
    serialport->write("O");
    qDebug("O\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    serialport->write("F");
    qDebug("F\n");
}
