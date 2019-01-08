#include "help.h"
#include "ui_help.h"
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);

    QPixmap pix(":/images/images/login.jpg");
       int w = ui->labelhelp->width();
       int h = ui->labelhelp->height();
       ui->labelhelp->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

help::~help()
{
    delete ui;
}

void help::on_contactBtn_clicked()
{




        QStringList items;
              items << tr("Zenon Naglik 777-777-333") << tr("Jakub Paszkot 222-333-444");

        bool ok;
        QString item = QInputDialog::getItem(this, tr("Kontakt"),
                                                   tr("Przedstawiciel:"), items, 0, false, &ok);
        if (ok && !item.isEmpty())
        {
            qDebug() << "Skontaktuj się : "<< item;
        }


}
