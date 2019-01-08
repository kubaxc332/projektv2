#include "json.h"
#include "ui_json.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>

json::json(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::json)
  mNetManager(new QNetworkAccessManager(this)),
  mNetReply(nullptr),
  mDataBuffer(new QByteArray)
{
    ui->setupUi(this);
}

json::~json()
{
    delete ui;
}


void json::on_downloadBtn_clicked()
{
    const QUrl API_ENDPOINT("https://www.qt.io/company");
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);

    mNetReply = mNetManager->get(request);
    connect(mNetReply,&QIODevice::readyRead,this,&Widget::dataReadyRead);
    connect(mNetReply,&QNetworkReply::finished,this,&Widget::dataReadFinished);

}

void json::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void json::dataReadFinished()
{
    if( mNetReply->error())
    {
        qDebug() << "Error : " << mNetReply->errorString();
    }else
    {
       qDebug() << "Data fetch finished : " << QString(*mDataBuffer);


       QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);

   QJsonArray array = doc.array();

       for ( int i = 0; i < array.size(); i++)
       {

           QJsonObject object = array.at(i).toObject();

           QVariantMap map = object.toVariantMap();

           QString title = map["title"].toString();

           ui->listWidget->addItem("["+ QString::number(i+1) + "] " + title);

       }
    }
}

