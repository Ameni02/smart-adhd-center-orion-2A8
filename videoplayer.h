#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
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



class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);

private slots:
    void videoStateChanged(QMediaPlayer::State state);
    void checkVideoEnded();

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
      QTimer *m_timer;
};

#endif // VIDEOPLAYER_H
