#include "qtinfo.h"
#include "ui_qtinfo.h"
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
qtinfo::qtinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtinfo)
{
    ui->setupUi(this);
    ui->setupUi(this);
    QPixmap pix(":/images/images/qt.svg");
       int w = ui->qtLabelPic->width();
       int h = ui->qtLabelPic->height();
       ui->qtLabelPic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

qtinfo::~qtinfo()
{
    delete ui;
}

void qtinfo::on_qtBtn_clicked()
{
    QString link = "https://www.qt.io/";
    QDesktopServices::openUrl(QUrl(link));
}

void qtinfo::on_actionQtQuit_triggered()
{

    statusBar()->showMessage("Trwa zamykanie okna...");
    QTimer::singleShot(3000,this,SLOT(quitApp()));
}
void qtinfo::quitApp()
{
QApplication::quit();
}

