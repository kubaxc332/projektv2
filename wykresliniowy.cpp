#include "wykresliniowy.h"
#include "ui_wykresliniowy.h"

wykresliniowy::wykresliniowy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wykresliniowy)
{
    ui->setupUi(this);
    mainLayout = new QGridLayout;
    axisX_0 = new QCategoryAxis();
    axisY_0 = new QValueAxis();

    axisX_1 = new QCategoryAxis();
    axisY_1 = new QValueAxis();

    axisX_2 = new QCategoryAxis();
    axisY_2 = new QValueAxis();

    series0 = new QScatterSeries();
    series1 = new QScatterSeries();
    series2 = new QScatterSeries();

    min0 = dataVector[presentRows + 1].toInt();
    max0 = dataVector[presentRows + 1].toInt();
    min1 = dataVector[(2*presentRows) + 1].toInt();
    max1 = dataVector[(2*presentRows) + 1].toInt();
    min2 = dataVector[(3*presentRows) + 1].toInt();
    max2 = dataVector[(3*presentRows) + 1].toInt();

    for(int j = 0; j < presentRows ; j++)
    {
       a1 = dataVector[j+1+presentRows].toInt();
       a2 = dataVector[j+1+(2*presentRows)].toInt();
       a3 = dataVector[j+1+(3*presentRows)].toInt();

       series0->append(QPoint(j, a1));
       series1->append(QPoint(j, a2));
       series2->append(QPoint(j, a3));

       if(min0 > a1 && col2Avl) min0 = a1;
       if(min1 > a2 && col3Avl) min1 = a2;
       if(min2 > a3 && col4Avl) min2 = a3;

       if(max0 < a1 && col2Avl) max0 = a1;
       if(max1 < a2 && col3Avl) max1 = a2;
       if(max2 < a3 && col4Avl) max2 = a3;
    }



    for(int j = 0; j < presentRows; j++)
    {
        axisX_0->append(dataVector[j+1], (j*20)+40);
        axisX_1->append(dataVector[j+1], (j*20)+40);
        axisX_2->append(dataVector[j+1], (j*20)+40);
    }

    m = 0;
    if(col2Avl)
    {
        chart_0 = new QChart();

        axisX_0->setLabelsPosition(QCategoryAxis::AxisLabelsPositionCenter);
        axisX_0->setRange(20,(presentRows*20));
        axisX_0->setTickAnchor(20);
        axisX_0->setTickInterval(20);
        axisX_0->setTickType(QValueAxis::TicksDynamic);
        axisY_0->setRange(min0, max0);
        //axisY_0->applyNiceNumbers();


        chart_0->addSeries(series0);
        chart_0->legend()->setVisible(true);


        series0->setName(dataVector[presentRows]);
        series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series0->setColor(Qt::red);
        series0->setMarkerSize(10.0);


        chart_0->addAxis(axisX_0, Qt::AlignBottom);
        chart_0->addAxis(axisY_0, Qt::AlignLeft);

        chartView_0 = new QChartView(chart_0);
        chartView_0->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView_0, m, 0);

   }

    if(col3Avl)
    {
        ++m;
        chart_1 = new QChart();
        chart_1->legend()->setVisible(true);

        axisX_1->setLabelsPosition(QCategoryAxis::AxisLabelsPositionCenter);
        axisX_1->setRange(20,(presentRows*20));
        axisX_1->setTickAnchor(20);
        axisX_1->setTickInterval(20);
        axisX_1->setTickType(QValueAxis::TicksDynamic);

        axisY_1->setRange(min1, max1);
        //axisY_1->applyNiceNumbers();

        series1->setName(dataVector[2*presentRows]);
        series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series1->setColor(Qt::yellow);
        series1->setMarkerSize(10.0);
        chart_1->addSeries(series1);
        chart_1->addAxis(axisX_1, Qt::AlignBottom);
        chart_1->addAxis(axisY_1, Qt::AlignLeft);
        chartView_1 = new QChartView(chart_1);
        chartView_1->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView_1, m, 0);
    }

    if(col4Avl)
    {
        ++m;
        chart_2 = new QChart();
        chart_2->legend()->setVisible(true);

        axisX_2->setLabelsPosition(QCategoryAxis::AxisLabelsPositionCenter);
        axisX_2->setRange(20,(presentRows*20));
        axisX_2->setTickAnchor(20);
        axisX_2->setTickInterval(20);
        axisX_2->setTickType(QValueAxis::TicksDynamic);

        axisY_2->setRange(min2, max2);
        //axisY_2->applyNiceNumbers();

        series2->setName(dataVector[3*presentRows]);
        series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series2->setColor(Qt::blue);
        series2->setMarkerSize(10.0);
        chart_2->addSeries(series2);

        chart_2->addAxis(axisX_2, Qt::AlignBottom);
        chart_2->addAxis(axisY_2, Qt::AlignLeft);
        chartView_2 = new QChartView(chart_2);
        chartView_2->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView_2, m, 0);
    }


    setLayout(mainLayout);


}

wykresliniowy::~wykresliniowy()
{
    delete ui;
}
