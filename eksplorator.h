#ifndef EKSPLORATOR_H
#define EKSPLORATOR_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class eksplorator;
}

class eksplorator : public QDialog
{
    Q_OBJECT

public:
    explicit eksplorator(QWidget *parent = nullptr);
    ~eksplorator();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QFileSystemModel * dirModel;
    QFileSystemModel * filesModel;

    Ui::eksplorator *ui;
};

#endif // EKSPLORATOR_H
