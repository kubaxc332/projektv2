#include "request.h"
#include "ui_request.h"
#include <QInputDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
request::request(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::request)
{
    ui->setupUi(this);
    helpButton = new QPushButton(this);
    QPixmap pix(":/images/images/help.jpg");
    int w = ui->requestLabel->width();
    int h = ui->requestLabel->height();
     ui->requestLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

request::~request()
{
    delete ui;
}


void request::on_helpButton_clicked()
{
    QMessageBox::information(this,"Informacja","Czy chcesz skontaktować się z naszym przedstawicielem ?",
                                            QMessageBox::Ok | QMessageBox::Cancel);


   QStringList items;
         items << tr("Zenon Naglik 777-777-333") << tr("Jakub Paszkot 222-333-444");

   bool ok;
   QString item = QInputDialog::getItem(this, tr("Kontakt"),
                                              tr("Przedstawiciel:"), items, 0, false, &ok);
   if (ok && !item.isEmpty())
   {
      statusBar()->showMessage("Skontaktuj się z:  " + item);
   }

}
