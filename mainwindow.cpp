#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    stopLoading = false;
    isLoaded = false;

    col1Checked = false;
    col2Checked = false;
    col3Checked = false;
    col4Checked = false;

    circleChartAvl = false;
    barChartAvl = false;

    sputterChartAvl = false;

    row = 1;
    col = 1;
    pos = 0;

    m = 0;
    presentRows = 20;

    tempStr = "";
    tempStr2 ="";

    col1_checkBox = new QCheckBox(parent);
    col2_checkBox = new QCheckBox(parent);
    col3_checkBox = new QCheckBox(parent);
    col4_checkBox = new QCheckBox(parent);

    ui->col1_checkBox->setChecked(false);
    ui->col2_checkBox->setChecked(false);
    ui->col3_checkBox->setChecked(false);
    ui->col4_checkBox->setChecked(false);

    apply_Btn = new QPushButton(parent);
    barChart_Btn = new QPushButton(parent);
    showData_Btn= new QPushButton(parent);
    circleChart_Btn = new QPushButton(parent);
    lineChart_Btn = new QPushButton(parent);
    clear_Btn = new QPushButton(parent);
    load_Btn = new QPushButton(parent);

    ui->apply_Btn->setEnabled(false);
    ui->barChart_Btn->setEnabled(false);
    ui->showData_Btn->setEnabled(false);
    ui->circleChart_Btn->setEnabled(false);
    ui->lineChart_Btn->setEnabled(false);
    ui->clear_Btn->setEnabled(false);
    ui->load_Btn->setEnabled(true);

    tableWidget = new QTableWidget(parent);
    tableWidget->setRowCount(20);
    tableWidget->setColumnCount(4);
    tableHorizontalHeader<<"column 1"<<"column 2"<<"column 3"<<"column 4";
    tableVerticalHeader<<"row 1"<<"row 2"<<"row 3"<<"row 4"
                       <<"row 5"<<"row 6"<<"row 7"<<"row 8"
                       <<"row 9"<<"row 10"<<"row 11"<<"row 12"
                       <<"row 13"<<"row 14"<<"row 15"<<"row 16"
                       <<"row 17"<<"row 18"<<"row 19"<<"row 20";
    ui->tableWidget->setHorizontalHeaderLabels(tableHorizontalHeader);
    ui->tableWidget->setVerticalHeaderLabels(tableVerticalHeader);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");
   // tableWidget->setGeometry(QApplication::desktop()->screenGeometry());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_load_Btn_clicked()
{


    //otworz okno szukajace pliku xslx
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("XML files (*.xlsx)"));

    usableFileName = "";

    for(int i=0, j=0; i < fileName.length(); i++)
    {
        usableFileName[j] = fileName[i];

        //MS uzywa slasha jako seperatora, a QT podwojnego bsckslasha, stad potrzeba zamienienia ich
        if(fileName[i] == '/')
        {
            usableFileName[j] = '\\';
            usableFileName[j+1] = '\\';
            j++;
        }
        else
        {
            usableFileName[j] = fileName[i];
        }
        j++;
    }

    stopLoading = false;

    /*******************************************************
     *
     *
     *               KOD LADUJACY PLIK .XLSX
     *
     *
     * *****************************************************/

    excel     = new QAxObject("Excel.Application");
    workbooks = excel->querySubObject("Workbooks");
    workbook  = workbooks->querySubObject("Open(const QString&)", usableFileName);
    if (!workbook)
    {
        isLoaded = false;
        QMessageBox::information(this, "", "Nie udalo sie zaladowac workbook");
    }
    else
    {
        sheets = workbook->querySubObject("Worksheets");
        if (!sheets)
        {
            isLoaded = false;
            QMessageBox::information(this, "", "Nie udalo sie zaladowac worksheets");
        }
        else
        {
            sheet = sheets->querySubObject("Item(int)", 1);
            excel->setProperty("EnableEvents", false);
            excel->dynamicCall("SetVisible(bool)", false);
            isLoaded = true;
        }
    }

    /******************************************************
     *
     *          KONIEC KODU LADUJACEGO KOD EXCELA
     *
     * ****************************************************/


    if(isLoaded) {

        //uniemozliwiamy korzystanie z innych przyciskow

        ui->barChart_Btn->setEnabled(false);
        ui->showData_Btn->setEnabled(true);
        ui->circleChart_Btn->setEnabled(false);
        ui->lineChart_Btn->setEnabled(false);
        ui->clear_Btn->setEnabled(true);
        ui->load_Btn->setEnabled(false);
        ui->apply_Btn->setEnabled(true);


        /****************************************************
         *
         * presentRows - jego wartosc jest nadawana po przejsciu petli przez pierwsza kolumne
         * (tj. tylko raz), przez co zapobiegamy przypadkowemu nadmiarowi danych w nastepnych kolumnach
         * (za domyslne przyjmujemy, ze pierwsza kolumna bez pierwszego wiersza reprezentuje kategorie danych
         * (obiekty typu QString). Domyslna wartosc (poczatkowa) wynosi 20 (tyle samo ile maksymalna liczba wierszy).
         *
         * Wartosci z komorek z Excela konwertowane sa na obiekty typu QString (ze wzgledu na zaimplementowane w bibliotece
         * standardowej funckje do obslugi stringow, kontrola tego typu danych jest latwa)
         *
         * Petle koncza sie z chwila zmiany stanu logicznego flagi stopLoading lub osiagniecia dostepnej liczby wierszy/kolumn.
         *
         * Przypadki wartosci niedozwolnych:
         * - pusty string w kol. >=1, w.1
         * - string zawierajacy liczbe(y) w kol.1 >= 1, w.1
         * - pusty string w kol.1, w. >1
         * - string zawierajacy litere(y) w kol. >1, w. >1
         *
         * Puste stringi w innych przypadkach sa ustawiane jako "0".
         *
         * Jesli wczytana komorka przejdzie testy (tj. nie spowoduje wyjscia z petli) zostaje wpisana do wektora
         * dataVector z odpowiednim indeksem.
         *
         *
         *
         * **************************************************/
        while((col <= ui->tableWidget->columnCount()) && (stopLoading == false))
        {

            while((row <= ui->tableWidget->rowCount()) && (row <= presentRows))
            {
                tempStr = sheet->querySubObject("Cells(int,int)",row,col)->dynamicCall("Value()").toString();

                if(row == 1 && (col >= 1))
                {
                   if(tempStr == "")
                   {
                       stopLoading = true;

                       //ustaw domyslne wartosci
                       col = 1;
                       row = 1;
                       pos = 0;
                       presentRows = 20;
                       dataVector.clear();
                       tempStr = "";
                       QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                       ui->barChart_Btn->setEnabled(false);
                       ui->showData_Btn->setEnabled(false);
                       ui->circleChart_Btn->setEnabled(false);
                       ui->lineChart_Btn->setEnabled(false);
                       ui->clear_Btn->setEnabled(true);
                       ui->load_Btn->setEnabled(false);
                       ui->apply_Btn->setEnabled(false);

                       break;
                   }
                   for (int j = 0; j < tempStr.size(); j++)
                   {
                        if(tempStr[j].isDigit())
                        {
                            stopLoading = true;

                            //ustaw domyslne wartosci
                            col = 1;
                            row = 1;
                            pos = 0;
                            presentRows = 20;
                            dataVector.clear();
                            tempStr = "";
                            QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                            ui->barChart_Btn->setEnabled(false);
                            ui->showData_Btn->setEnabled(false);
                            ui->circleChart_Btn->setEnabled(false);
                            ui->lineChart_Btn->setEnabled(false);
                            ui->clear_Btn->setEnabled(true);
                            ui->apply_Btn->setEnabled(false);
                            ui->load_Btn->setEnabled(false);

                            break;

                        }
                        else
                        {
                            //nic nie rob
                        }
                   }

                }

                if((row > 1) && (col == 1))
                {
                    if(tempStr == "")
                    {
                        break;
                    }
                }

                if(row > 1 && col > 1)
                {
                   for (int j = 0; j < tempStr.size(); j++)
                   {
                        if(tempStr[j].isDigit())
                        {
                            //nic nie rob
                        }
                        else
                        {
                            stopLoading = true;

                            //ustaw domyslne wartosci
                            col = 1;
                            row = 1;
                            pos = 0;
                            presentRows = 20;
                            dataVector.clear();
                            tempStr = "";
                            QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                            ui->barChart_Btn->setEnabled(false);
                            ui->showData_Btn->setEnabled(false);
                            ui->circleChart_Btn->setEnabled(false);
                            ui->lineChart_Btn->setEnabled(false);
                            ui->clear_Btn->setEnabled(true);
                            ui->apply_Btn->setEnabled(false);
                            ui->load_Btn->setEnabled(false);

                            break;
                        }
                   }

                }

                if(tempStr == "")
                {
                    dataVector.insert(pos, "0");
                }
                else {
                    dataVector.insert(pos, sheet->querySubObject("Cells(int,int)",row,col)->dynamicCall("Value()").toString());
                }
                pos++;
                row++;
            }

            if(col == 1) {
                presentRows = row - 1;
            }

            col++;
            row = 1;
        }
    }
}

void MainWindow::on_barChart_Btn_clicked()
{
    wykres wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_circleChart_Btn_clicked()
{
     wykresKolowy wykres;
     wykres.setModal(true);
     wykres.exec();
}

void MainWindow::on_lineChart_Btn_clicked()
{
    wykresliniowy wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_clear_Btn_clicked()
{
     //ustaw domyslne wartosci
    ui->barChart_Btn->setEnabled(false);
    ui->showData_Btn->setEnabled(false);
    ui->circleChart_Btn->setEnabled(false);
    ui->lineChart_Btn->setEnabled(false);
    ui->clear_Btn->setEnabled(false);
    ui->load_Btn->setEnabled(true);
    ui->apply_Btn->setEnabled(false);

    ui->col1_checkBox->setChecked(false);
    ui->col2_checkBox->setChecked(false);
    ui->col3_checkBox->setChecked(false);
    ui->col4_checkBox->setChecked(false);

    circleChartAvl = false;
    barChartAvl = false;
    sputterChartAvl = false;


    tempStr="";
    tempStr2="";

    stopLoading = false;
    isLoaded = false;
    row = 1;
    col = 1;
    pos = 0;
    m = 0;
    presentRows = 20;
    dataVector.clear();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->rowCount(); j++)
        {
            ui->tableWidget->setItem(j,i, new QTableWidgetItem(""));
            m++;
        }
    }
   workbook->dynamicCall("Close()");
   excel->dynamicCall("Quit()");
   delete excel;
}

void MainWindow::on_showData_Btn_clicked()
{
    m = 0;

    //petla wczytujaca dane z wektora dataClear do tabeli

    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {

        for(int j = 0; j < presentRows ; j++)
        {
            QTableWidgetItem *itemTemp = new QTableWidgetItem(dataVector[m]);
            //itemTemp->setSizeHint( tableWidget->sizeHint() );
            ui->tableWidget->setItem(j,i, itemTemp);
            m++;
        }
    }



}

/************************************
 *
 * Funckja: checkForPermission()
 *
 * Zastosowanie: Sprawdza zmienne bool zw. z aktywacja checkBoxow (Kolumna 1-4) i na ich podstawie
 * wydaje pozwolenia na otwarcie poszczegolnych typow wykresów.
 *
 * Uwagi: Po sprawdzeniu ww. zmiennych, funkcja wywoluje checkForCharts()
 *        Funkcja pobiera dane po nacisnieciu przycisku "Zastosuj" (por. on_apply_Btn_clicked())
 *
 ************************************/

void MainWindow::checkForPermission()
{
    if(col1Checked)
    {
        if(col2Checked && col3Checked && col4Checked)
        {
            col2Avl = true;
            col3Avl = true;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(col2Checked && !col3Checked && !col4Checked)
        {
            col2Avl = true;
            col3Avl = false;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && col3Checked && !col4Checked)
        {
            col2Avl = false;
            col3Avl = true;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && !col3Checked && col4Checked)
        {
            col2Avl = false;
            col3Avl = false;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && !col3Checked && !col4Checked)
        {
            col2Avl = false;
            col3Avl = false;
            col4Avl = false;

            circleChartAvl = false;
            barChartAvl = false;
            sputterChartAvl = false;
        }
        if(col2Checked && col3Checked && !col4Checked)
        {
            col2Avl = true;
            col3Avl = true;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(col2Checked && !col3Checked && col4Checked)
        {
            col2Avl = true;
            col3Avl = false;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(!col2Checked && col3Checked && col4Checked)
        {
            col2Avl = false;
            col3Avl = true;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }

    }
    else
    {
        col2Avl = false;
        col3Avl = false;
        col4Avl = false;

        circleChartAvl = false;
        barChartAvl = false;
        sputterChartAvl = false;
    }
    checkForCharts();
}

/********************************
 *
 * Funckcja: checkForCharts()
 *
 * Zastosowanie: Sprawdza pozwolenia na stosowanie danych typow wykresow i uaktywnia odpowiednie przyciski
 *
 * Uwagi: Korzysta z wynikow dzialania funkcji checkForPermission() i jest przez nia (i tylko przez nia) wywolywana
 *
 * ******************************/

void MainWindow::checkForCharts()
{
    if(circleChartAvl)
    {
        ui->circleChart_Btn->setEnabled(true);
    }
    else
    {
        ui->circleChart_Btn->setEnabled(false);
    }

    if(barChartAvl)
    {
        ui->barChart_Btn->setEnabled(true);
    }
    else
    {
        ui->barChart_Btn->setEnabled(false);
    }

    if(sputterChartAvl)
    {
        ui->lineChart_Btn->setEnabled(true);
    }
    else
    {
        ui->lineChart_Btn->setEnabled(false);
    }
}

/*******************************
 *
 * Funkcja: on_apply_Btn_clicked()
 *
 * Zastosowanie: Klikniecie przycisku "Zastosuj" powoduje sprawdzenie stanu checkboxow "Kolumna 1-4"
 *              i zmiane wartosci stosownych flag
 *
 * Uwagi: Wywoluje checkForPermission()
 *
 * ****************************/

void MainWindow::on_apply_Btn_clicked()
{
    if(ui->col1_checkBox->isChecked())
    {
        col1Checked = true;
    }
    else
    {
        col1Checked = false;
    }

    if(ui->col2_checkBox->isChecked())
    {
        col2Checked = true;
    }
    else
    {
        col2Checked = false;
    }

    if(ui->col3_checkBox->isChecked())
    {
        col3Checked = true;
    }
    else
    {
        col3Checked = false;
    }

    if(ui->col4_checkBox->isChecked())
    {
        col4Checked = true;
    }
    else
    {
        col4Checked = false;
    }

       checkForPermission();
}

void MainWindow::on_actionZako_cz_triggered()
{

    int ret = QMessageBox::critical(this,"Uwaga!","Czy chcesz zakończyć działanie aplikacji  ?",
                                            QMessageBox::Ok | QMessageBox::Cancel);


    if ( ret == QMessageBox::Ok)
    {
        statusBar()->showMessage("Aplikacja zostanie zamknięta w ciągu 4s...");
        QTimer::singleShot(4000,this,SLOT(quitApp()));
    }




}
void MainWindow::quitApp()
{
    QApplication::quit();
}

void MainWindow::on_actionEksplorator_plik_w_triggered()
{
    eksplorator eksplorator;
    eksplorator.setModal(true);
    eksplorator.exec();
}

void MainWindow::on_actionDodaj_opis_triggered()
{
    opis.show();
}

void MainWindow::on_actionZg_o_problem_triggered()
{

    problem.show();
}

void MainWindow::on_actionDrukuj_triggered()
{
    //nic nie rob
}

void MainWindow::on_actionO_programie_triggered()
{
    info.show();
}

void MainWindow::on_actionGitHub_triggered()
{
    github.show();
}

void MainWindow::on_actionQt_triggered()
{
    qtinfo.show();

}

void MainWindow::on_actionWykres_s_upkowy_2_triggered()
{
    wykres wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_actionWykres_ko_owy_triggered()
{
    wykresKolowy wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_actionWykres_liniowy_triggered()
{
    wykresliniowy wykres;
    wykres.setModal(true);
    wykres.exec();
}


void MainWindow::on_actionPoka_dane_triggered()
{

    m = 0;

    //petla wczytujaca dane z wektora dataClear do tabeli

    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {

        for(int j = 0; j < presentRows ; j++)
        {
            QTableWidgetItem *itemTemp = new QTableWidgetItem(dataVector[m]);
            //itemTemp->setSizeHint( tableWidget->sizeHint() );
            ui->tableWidget->setItem(j,i, itemTemp);
            m++;
        }
    }


}

void MainWindow::on_actionWyczy_triggered()
{
    //ustaw domyslne wartosci
   ui->barChart_Btn->setEnabled(false);
   ui->showData_Btn->setEnabled(false);
   ui->circleChart_Btn->setEnabled(false);
   ui->lineChart_Btn->setEnabled(false);
   ui->clear_Btn->setEnabled(false);
   ui->load_Btn->setEnabled(true);
   ui->apply_Btn->setEnabled(false);

   ui->col1_checkBox->setChecked(false);
   ui->col2_checkBox->setChecked(false);
   ui->col3_checkBox->setChecked(false);
   ui->col4_checkBox->setChecked(false);

   circleChartAvl = false;
   barChartAvl = false;
   sputterChartAvl = false;


   tempStr="";
   tempStr2="";

   stopLoading = false;
   isLoaded = false;
   row = 1;
   col = 1;
   pos = 0;
   m = 0;
   presentRows = 20;
   dataVector.clear();
   for(int i = 0; i < ui->tableWidget->columnCount(); i++)
   {
       for(int j = 0; j < ui->tableWidget->rowCount(); j++)
       {
           ui->tableWidget->setItem(j,i, new QTableWidgetItem(""));
           m++;
       }
   }
  workbook->dynamicCall("Close()");
  excel->dynamicCall("Quit()");
  delete excel;
}
