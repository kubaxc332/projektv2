#include "opiswykres.h"
#include "ui_opiswykres.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QTimer>
opiswykres::opiswykres(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::opiswykres)
{
    ui->setupUi(this);
}

opiswykres::~opiswykres()
{
    delete ui;
}

void opiswykres::on_SaveBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Zapisz jako");
    if( filename.isEmpty())
        return;

    QFile file(filename);


    if( !file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

void opiswykres::on_OpenBtn_clicked()
{
    QString  fileContent;

    QString filename = QFileDialog::getOpenFileName(this,"Otwórz plik");

    if(filename.isEmpty())
    return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull())
    {
         fileContent.append(line);
        line = in.readLine();
    }

    file.close();

    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
}

void opiswykres::on_selectBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Wybierz plik");
    if( filename.isEmpty())
        return;
    ui->sourceLineEdit->setText(filename);
}

void opiswykres::on_CopyBtn_clicked()
{
    QString srcFileName = ui->sourceLineEdit->text();
    QString destFileName = ui->destLineEdit->text();

    if( srcFileName.isEmpty() || destFileName.isEmpty())
        return;

    QFile file(srcFileName);
    if( file.copy(destFileName))
    {
        QMessageBox::information(this,"Udało się!","Kopiowanie pliku powiodło się");
        statusBar()->showMessage("Kopiowane pliku się powiodło!");
    }else
    {
        QMessageBox::information(this,"Błąd!","Kopiowanie pliku nie powiodło się");
        statusBar()->showMessage("Kopiowane pliku się nie powiodło!");
    }
}


void opiswykres::on_actionDescriptionClose_triggered()
{

}

void opiswykres::on_pushButtonFont_clicked()
{
    bool ok;
         QFont font = QFontDialog::getFont(
                         &ok, QFont("Helvetica [Cronyx]", 10), this);
         if (ok) {
             ui->textEdit->setFont(font);

         } else {
             QMessageBox::information(this,"Wiadomość","Użytkownik nie wybrał rodzaju czcionki!");
         }
}

void opiswykres::on_pushButtonColor_clicked()
{
    QPalette palette = ui->textEdit->palette();

        QColor color = palette.color(QPalette::WindowText);

        QColor chosenColor = QColorDialog::getColor(color,this,"Wybierz kolor czcionki");

        if(chosenColor.isValid())
        {
            palette.setColor(QPalette::WindowText,chosenColor);
            ui->textEdit->setPalette(palette);

        }else
        {
          statusBar()->showMessage("Aplikacja zostanie zamknięta w ciągu 4s...");
        }
}

void opiswykres::on_actionQuitDescription_triggered()
{
    statusBar()->showMessage("Trwa zamykanie okna...");
    QTimer::singleShot(3000,this,SLOT(quitApp()));
}
void opiswykres::quitApp()
{
    QApplication::quit();
}
