#include "chatbot.h"
#include <QApplication>

Chatbot::Chatbot()//m_apiKey(m_apikey),m_networkManager(new QNetworkAccessManager)
{

}

QString Chatbot::sendMessage(QString &message)
{
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QString url = QString("https://api.wit.ai/message?v=20230215&q=%1").arg(message);
        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setRawHeader("Authorization", QString("Bearer %1").arg("5BQPUYRCQXIW5O5WVAZG5AKA7VOE44BE").toUtf8());
        QNetworkReply *reply = manager->get(request);
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        if (reply->error() != QNetworkReply::NoError) {
            QString errorMessage = reply->errorString();
            qDebug() << "Network error: " << errorMessage;
            return QString();
        }
        QString response = QString(reply->readAll());
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
        QString intent = jsonDoc["intents"][0]["name"].toString();
         qDebug() << intent;
        return intent;
    }


