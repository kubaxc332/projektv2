#include "eksplorator.h"
#include "ui_eksplorator.h"
#include <QInputDialog>
eksplorator::eksplorator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eksplorator)
{
    ui->setupUi(this);

    QString path = "D:/";// /home/username/Downloads


    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    dirModel->setRootPath(path);
    ui->treeView->setModel(dirModel);


    filesModel = new QFileSystemModel(this);
    filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filesModel->setRootPath(path);
    ui->listView->setModel(filesModel);
}

eksplorator::~eksplorator()
{
    delete ui;
}

void eksplorator::on_treeView_clicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filesModel->setRootPath(path+"/"));
}

void eksplorator::on_pushButton_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    QString name = QInputDialog::getText(this,"Nowy folder","Podaj nazwę");
    if(name.isEmpty()) return;
    dirModel->mkdir(index,name);
}

void eksplorator::on_pushButton_2_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    if(dirModel->fileInfo(index).isDir())
    {
     dirModel->rmdir(index);
    }

    else
    {
       dirModel->remove(index);
    }
}
