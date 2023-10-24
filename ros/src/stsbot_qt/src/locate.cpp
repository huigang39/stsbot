#include "locate.h"
#include "ui_locate.h"
#include "mainwindow.h"
#include "eForm.h"

locate::locate(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::locate)
{
    ui->setupUi(this);
    this->setWindowTitle("导航");
}

locate::~locate()
{
    delete ui;
}

void locate::on_guidButton_clicked()
{
    MainWindow *m = new MainWindow;
    this->close();
    m->show();
}

void locate::on_view_2_clicked()
{
    eForm *e = new eForm();
    this->close();
    e->show();
}
