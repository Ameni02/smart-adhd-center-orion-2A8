#ifndef CHATBOT_H
#define CHATBOT_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>


class Chatbot : public QObject
{
    Q_OBJECT

public:
    Chatbot();
    QString sendMessage(QString &message);


private:
    QNetworkAccessManager* m_networkManager;
};

#endif // CHATBOT_H
