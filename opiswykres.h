#ifndef OPISWYKRES_H
#define OPISWYKRES_H

#include <QMainWindow>

namespace Ui {
class opiswykres;
}

class opiswykres : public QMainWindow
{
    Q_OBJECT

public:
    explicit opiswykres(QWidget *parent = nullptr);
    ~opiswykres();

private slots:
    void on_SaveBtn_clicked();

    void on_OpenBtn_clicked();

    void on_selectBtn_clicked();

    void on_CopyBtn_clicked();

    void on_actionDescriptionClose_triggered();

    void on_pushButtonFont_clicked();

    void on_pushButtonColor_clicked();

    void on_actionQuitDescription_triggered();

    void quitApp();

private:
    Ui::opiswykres *ui;
};

#endif // OPISWYKRES_H
