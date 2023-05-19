#include "VideoWidget.h"
#include "qboxlayout.h"
#include "qmediaplayer.h"
#include "qwidget.h"

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    layout->addWidget(videoWidget);
    setLayout(layout);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &VideoWidget::handleMediaStatusChanged);
    player->setVideoOutput(videoWidget);
    player->setSource(QUrl::fromLocalFile("C:/Users/Si Taz/Desktop/logo main.avi"));
    player->play();
}

VideoWidget::~VideoWidget() {
    player->stop();
}

void VideoWidget::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        player->stop();
        emit videoFinished();
    }
}
