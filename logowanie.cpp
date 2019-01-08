#include "logowanie.h"
#include "ui_logowanie.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
logowanie::logowanie(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::logowanie)
{
    ui->setupUi(this);
    QPixmap pix(":/images/images/login.jpg");
       int w = ui->label_pic->width();
       int h = ui->label_pic->height();
       ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

logowanie::~logowanie()
{
    delete ui;
}

void logowanie::on_logOn_Btn_clicked()
{
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

        if(username ==  "user" && password == "chart")
        {
            QMessageBox::information(this, "Login", "Udało się zalogować!");
            MainWindow *w = new MainWindow();
            w->show();
            this->close();

        }
        else
        {
            QMessageBox::warning(this, "Login", "Nazwa uzytkownika lub haslo niepoprawne");
        }
}


