#ifndef REQUEST_H
#define REQUEST_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class request;
}

class request : public QMainWindow
{
    Q_OBJECT

public:
    explicit request(QWidget *parent = nullptr);
    ~request();

private slots:


    void on_helpButton_clicked();

private:
    Ui::request *ui;

    QPushButton *helpButton;
};

#endif // REQUEST_H
