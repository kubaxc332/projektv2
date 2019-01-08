#ifndef INFO_H
#define INFO_H

#include <QMainWindow>

namespace Ui {
class info;
}

class info : public QMainWindow
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
    ~info();

private slots:
    void on_actionInfoQuit_triggered();
    void quitApp();

private:
    Ui::info *ui;
};

#endif // INFO_H
