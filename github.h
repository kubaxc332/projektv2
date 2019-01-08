#ifndef GITHUB_H
#define GITHUB_H

#include <QMainWindow>

namespace Ui {
class github;
}

class github : public QMainWindow
{
    Q_OBJECT

public:
    explicit github(QWidget *parent = nullptr);
    ~github();

private slots:
    void on_actionGitClose_triggered();
        void quitApp();

        void on_gitBtn_clicked();

private:
    Ui::github *ui;
};

#endif // GITHUB_H
