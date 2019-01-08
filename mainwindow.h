#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAxObject>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "wykreskolowy.h"
#include "wykres.h"
#include "wykresliniowy.h"
#include "eksplorator.h"
#include "opiswykres.h"
#include "globals.h"
#include "info.h"
#include "problem.h"
#include "github.h"
#include "qtinfo.h"
class QPushButton;
class QAxObject;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_load_Btn_clicked();

    void on_barChart_Btn_clicked();

    void on_showData_Btn_clicked();

    void on_circleChart_Btn_clicked();

    void on_lineChart_Btn_clicked();

    void on_clear_Btn_clicked();



    void on_apply_Btn_clicked();

    void on_actionZako_cz_triggered();
    void quitApp();

    void on_actionEksplorator_plik_w_triggered();

    void on_actionDodaj_opis_triggered();

    void on_actionZg_o_problem_triggered();

    void on_actionDrukuj_triggered();

    void on_actionO_programie_triggered();

    void on_actionGitHub_triggered();

    void on_actionQt_triggered();

    void on_actionWykres_s_upkowy_2_triggered();

    void on_actionWykres_ko_owy_triggered();

    void on_actionWykres_liniowy_triggered();

    void on_actionPoka_dane_triggered();

    void on_actionWyczy_triggered();

private:



    opiswykres opis;
    info info;
    problem problem;
    github github;
    qtinfo qtinfo;
    void checkForCharts();
    void checkForPermission();

    bool isLoaded;
    bool stopLoading;
    bool col1Checked, col2Checked, col3Checked, col4Checked;


    int row, col, pos;
    int m;


    QString tempStr, tempStr2;
    QString fileName, usableFileName;

    QStringList tableVerticalHeader;
    QStringList tableHorizontalHeader;

    QTableWidget *tableWidget;

    QPushButton *apply_Btn;
    QPushButton *barChart_Btn;
    QPushButton *showData_Btn;
    QPushButton *circleChart_Btn;
    QPushButton *lineChart_Btn;
    QPushButton *load_Btn;
    QPushButton *clear_Btn;

    QCheckBox *col1_checkBox;
    QCheckBox *col2_checkBox;
    QCheckBox *col3_checkBox;
    QCheckBox *col4_checkBox;

    QAxObject* excel ;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
