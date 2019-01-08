#ifndef PROBLEM_H
#define PROBLEM_H

#include <QMainWindow>


namespace Ui {
class problem;
}

class problem : public QMainWindow
{
    Q_OBJECT

public:
    explicit problem(QWidget *parent = nullptr);
    ~problem();

private slots:


    void on_problemBtn_clicked();

    void on_actionQuitProblem_triggered();
      void quitApp();

private:
    Ui::problem *ui;

};

#endif // PROBLEM_H
