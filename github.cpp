#include "github.h"
#include "ui_github.h"
#include <QPixmap>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
github::github(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::github)
{
    ui->setupUi(this);
    QPixmap pix(":/images/images/github.png");
       int w = ui->gitHubLabel->width();
       int h = ui->gitHubLabel->height();
       ui->gitHubLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


}

github::~github()
{
    delete ui;
}

void github::on_actionGitClose_triggered()
{
    statusBar()->showMessage("Trwa zamykanie okna...");
    QTimer::singleShot(3000,this,SLOT(quitApp()));
}
void github::quitApp()
{
QApplication::quit();
}

void github::on_gitBtn_clicked()
{
    QString link = "https://github.com/ZNaglik";
    QDesktopServices::openUrl(QUrl(link));
}
