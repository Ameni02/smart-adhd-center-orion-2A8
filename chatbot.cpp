#include "chatbot.h"

ChatBot::ChatBot(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_botpressUrl = "https://mediafiles.botpress.cloud/5b976b88-63b3-470d-9f2a-bcc847d205f9/webchat/bot.html";

    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &ChatBot::onBotpressResponse);
}

ChatBot::~ChatBot()
{
    delete m_networkManager;
}

QString ChatBot::ask(const QString &question)
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_botpressUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString requestBody = QString("{\"type\": \"text\", \"content\": \"%1\"}").arg(question);
    QNetworkReply *reply = m_networkManager->post(request, requestBody.toUtf8());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString response = reply->readAll();
    reply->deleteLater();

    return response;
}

void ChatBot::onBotpressResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    QString response = reply->readAll();
    reply->deleteLater();
}
