#include "problem.h"
#include "ui_problem.h"
#include <QInputDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

problem::problem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::problem)
{
    ui->setupUi(this);



    QPixmap pix(":/images/images/help.jpg");
    int w = ui->problemLabel->width();
    int h = ui->problemLabel->height();
     ui->problemLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

problem::~problem()
{
    delete ui;
}



void problem::on_problemBtn_clicked()
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
      statusBar()->showMessage("Skontaktuj się z:" + item);
   }
}

void problem::on_actionQuitProblem_triggered()
{
    statusBar()->showMessage("Trwa zamykanie okna...");
    QTimer::singleShot(3000,this,SLOT(quitApp()));
}
void problem::quitApp()
{
    QApplication::quit();
}
