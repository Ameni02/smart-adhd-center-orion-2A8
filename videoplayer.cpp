#include "videoPlayer.h"
#include "qmediaplayer.h"
#include "qtimer.h"
#include "qvideowidget.h"
#include "qwidget.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>
#include <QDateTime>
#include <QTimer>
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the video player and video widget
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);

    // Set the media file path and show the video widget
    player->setSource(QUrl::fromLocalFile("path/to/video/file"));
    setCentralWidget(videoWidget);

    // Connect the player state changed signal to a slot
    connect(player, &::QMediaPlayer::sourceChanged, this, &VideoPlayer::videoStateChanged);

    // Start playing the video and a timer to check when the video ends
    player->play();
    m_timer = new QTimer(this);
    connect(&m_timer, &QTimer::timeout, this, &VideoPlayer::onTimeout);

    m_timer->start(100);
}

void VideoPlayer::videoStateChanged(QMediaPlayer::State stat)
{
    if (stat == QMediaPlayer::StoppedState) {
        show();
    }
}

void VideoPlayer::checkVideoEnded()
{
    if (player->duration() > 0 && player->position() >= player->duration()) {
        m_timer->stop();
        player->stop();
    }
}
