#include "wykreskolowy.h"
#include "mainwindow.h"
#include "ui_wykreskolowy.h"

wykresKolowy::wykresKolowy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wykresKolowy)
{
    ui->setupUi(this);

     mainLayout = new QGridLayout;


     series0 = new QPieSeries();
     series1 = new QPieSeries();
     series2 = new QPieSeries();

     for(int j = 0; j < presentRows ; j++)
     {
        series0->append(dataVector[j+1], dataVector[j+1+(presentRows)].toInt());
        series1->append(dataVector[j+1], dataVector[j+1+(2*presentRows)].toInt());
        series2->append(dataVector[j+1], dataVector[j+1+(3*presentRows)].toInt());
     }

     m = 1;

    if(col2Avl)
    {
        createNewChart(chart, series0, chartView, m);
     }

     if(col3Avl)
     {
         ++m;
         createNewChart(chart, series1, chartView, m);
     }

     if(col4Avl)
     {
         ++m;
        createNewChart(chart, series2, chartView, m);
     }

     setLayout(mainLayout);

     setWindowTitle(tr("Wykres kolowy"));
}

wykresKolowy::~wykresKolowy()
{
    delete ui;
}

void wykresKolowy::createNewChart(QChart *chart, QPieSeries *series, QChartView *chartView, int counter)
{
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Wykres " + dataVector[m*presentRows]);
    chart->legend()->show();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView, 0, counter);
}
