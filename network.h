#ifndef NETWORK_H
#define NETWORK_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
namespace Ui {
class network;
}

class network : public QMainWindow
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = nullptr);
    ~network();

private slots:


    void dataReadyRead();
    void dataReadFinished();


    void on_networkBtn_clicked();

private:
    Ui::network *ui;
    QNetworkAccessManager * mNetManager;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;
};

#endif // NETWORK_H
