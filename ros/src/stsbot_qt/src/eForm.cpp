
#include "ui_eForm.h"
#include "mainwindow.h"
#include "eForm.h"
#include "locate.h"

eForm::eForm(QWidget *parent) : QWidget(parent),
                                ui(new Ui::eForm)
{
    ui->setupUi(this);
}
eForm::~eForm()
{
    delete ui;
}

void eForm::on_confirmButton_clicked()
{
    this->close();
}

void eForm::on_cancelButton_clicked()
{
    MainWindow *m = new MainWindow();
    this->close();
    m->show();
}

void eForm::on_guidButton_clicked()
{
    locate *l = new locate();
    this->close();
    l->show();
}

void eForm::on_view_clicked()
{
    locate *l = new locate();
    this->close();
    l->show();
}
