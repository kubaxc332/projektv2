#ifndef QTINFO_H
#define QTINFO_H

#include <QMainWindow>

namespace Ui {
class qtinfo;
}

class qtinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtinfo(QWidget *parent = nullptr);
    ~qtinfo();

private slots:
    void on_qtBtn_clicked();

    void on_actionQtQuit_triggered();
    void quitApp();

private:
    Ui::qtinfo *ui;
};

#endif // QTINFO_H
