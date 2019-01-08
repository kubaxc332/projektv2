#include "wykres.h"
#include "ui_wykres.h"

wykres::wykres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wykres)
{
    ui->setupUi(this);

    series = new QHorizontalPercentBarSeries();
    mainLayout = new QGridLayout;
    chart = new QChart();
    axis = new QBarCategoryAxis();
    chartView = new QChartView(chart);

    QBarSet *set0 = new QBarSet(dataVector[presentRows]);
    QBarSet *set1 = new QBarSet(dataVector[2*presentRows]);
    QBarSet *set2 = new QBarSet(dataVector[3*presentRows]);

    for(int j = 0; j < presentRows; j++)
    {
        *set0 << dataVector[j+1+presentRows].toInt();
        *set1 << dataVector[j+1+(2*presentRows)].toInt();
        *set2 << dataVector[j+1+(3*presentRows)].toInt();
    }

    for(int j = 0; j < presentRows; j++)
    {
        categories << dataVector[j+1];
    }

    if(col2Avl) series->append(set0);
    if(col3Avl) series->append(set1);
    if(col4Avl) series->append(set2);


    chart->addSeries(series);
    chart->setTitle("Wykres slupkowy");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisY(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView, 0, 0);
    setLayout(mainLayout);

    setWindowTitle(tr("Wykres slupkowy"));
}

wykres::~wykres()
{
    delete ui;
}
