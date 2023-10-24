#ifndef LOCATE_H
#define LOCATE_H

#include <QWidget>

namespace Ui
{
    class locate;
}

class locate : public QWidget
{
    Q_OBJECT

public:
    explicit locate(QWidget *parent = nullptr);
    ~locate();

private slots:
    void on_guidButton_clicked();

    void on_view_2_clicked();

private:
    Ui::locate *ui;
};

#endif // LOCATE_H
