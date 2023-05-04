#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class ChatBot : public QObject
{
    Q_OBJECT

public:
    explicit ChatBot(QObject *parent = nullptr);
    ~ChatBot();

    QString ask(const QString &question);

private slots:
    void onBotpressResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_botpressUrl;
};

#endif // CHATBOT_H
