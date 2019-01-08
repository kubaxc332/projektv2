#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class logowanie;
}

class logowanie : public QMainWindow
{
    Q_OBJECT

public:
    explicit logowanie(QWidget *parent = nullptr);
    ~logowanie();

private slots:
    void on_logOn_Btn_clicked();

private:
    QString username;
    QString password;

    Ui::logowanie *ui;
};

#endif // LOGOWANIE_H
