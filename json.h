#ifndef JSON_H
#define JSON_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class json;
}

class json : public QWidget
{
    Q_OBJECT

public:
    explicit json(QWidget *parent = nullptr);
    ~json();

private slots:
    void dataReadyRead();
    void dataReadFinished();
    void on_downloadBtn_clicked();

private:
    Ui::json *ui;
    QNetworkAccessManager * mNetManager;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;

}

#endif // JSON_H



