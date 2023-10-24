#ifndef EFORM_H
#define EFORM_H

#include <QWidget>

namespace Ui
{

    class eForm;
}

class eForm : public QWidget
{
    Q_OBJECT

public:
    explicit eForm(QWidget *parent = nullptr);
    ~eForm();

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

    void on_guidButton_clicked();

    void on_view_clicked();

private:
    Ui::eForm *ui;
};

#endif // EFORM_H
