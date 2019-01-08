#include "info.h"
#include "ui_info.h"
#include <QPixmap>
#include <QTimer>
#include <QLabel>
info::info(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    QPixmap pix(":/images/images/infoa.jpg");
       int w = ui->infoLabel->width();
       int h = ui->infoLabel->height();
       ui->infoLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


}

info::~info()
{
    delete ui;
}

void info::on_actionInfoQuit_triggered()
{

        statusBar()->showMessage("Trwa zamykanie okna...");
        QTimer::singleShot(3000,this,SLOT(quitApp()));



}
void info::quitApp()
{
    QApplication::quit();
}
