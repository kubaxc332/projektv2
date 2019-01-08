#ifndef WYKRES_H
#define WYKRES_H

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include "globals.h"


namespace Ui {
class wykres;
}

class wykres : public QDialog
{
    Q_OBJECT

public:
    explicit wykres(QWidget *parent = nullptr);
    ~wykres();

private:
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;

    QHorizontalPercentBarSeries *series;
    QBarCategoryAxis *axis;
    QStringList categories;
    QGridLayout *mainLayout;
    QChartView *chartView;
    QChart *chart;
    Ui::wykres *ui;
};

#endif // WYKRES_H
