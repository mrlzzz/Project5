#include "postreq2.h"
#include "transblock.h"
#include "terminal.h"
#include "ui_terminal.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>

#include <QtNetwork/QNetworkAccessManager>

PostRequest::PostRequest(int amount, QString cur, QString terID, QString PAN, QString PIN)
{
    //Setup HTTP POST request destination

    QUrl serviceUrl = QUrl("https://payment-app-mrl.herokuapp.com/post");
    QNetworkRequest networkRequest(serviceUrl);

    //Setup data to send

    QDate date = date.currentDate();
    QTime time = time.currentTime();

    QJsonObject json;
    json.insert("timestamp", date.toString() + " " + time.toString());
    json.insert("amount", amount);
    json.insert("currency", cur);
    json.insert("terminalID", terID);
    json.insert("pan", PAN);
    json.insert("pin", PIN);
    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    //HTTP POST Headers

    QByteArray postDataSize = QByteArray::number(postData.size());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, postDataSize);




    //HTTPS Config

//    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
//    config.setProtocol(QSsl::TlsV1_2);
//    networkRequest.setSslConfiguration(config);

    //NAM and slots (SLOT will run when connection is done, has to be defined)

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(serviceRequestFinish(QNetworkReply*)));

    //Send POST request

    networkManager->post(networkRequest, postData);

//    curl -X POST -d "{\"name\": \"Jack\", \"text\": \"HULLO\"}" -H "Content-Type: application/json" localhost:3000/post



//    QUrl params;
//    QUrlQuery query;
//    query.addQueryItem("name","string1");
//    query.addQueryItem("text","string2");

//    params.setQuery(query);

//    postData = params.toEncoded(QUrl::RemoveFragment);

    // Call the webservice



//    networkRequest.setRawHeader("User-Agent", "My app name v0.1");
//    networkRequest.setRawHeader("X-Custom-User-Agent", "My app name v0.1");

//    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



}

void PostRequest::serviceRequestFinish(QNetworkReply* rep) {
    qDebug() << "POST REQUEST SENT";
    qDebug() << rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Reply from server: " << rep->readAll();


}
