
#ifndef MYVIDEOCAPTURE_H
#define MYVIDEOCAPTURE_H
#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

#ID
class myvideocapture : public QThread
{
    Q_OBJECT
public:
    myvideocapture(QObject *parent = nullptr);
    QPixmap pixmap() const
    {
        return mPixmap;
    }
signals:
    void newPixmapCaptured ();
private:
    QPixmap mPixmap;
    cv::Mat mFrame;
    cv::VideoCapture mVideoCap;
    QImage  cvMatToQImage(const cv::Mat &inMat );
    QPixmap cvMatToQPixmap(const cv::Mat &inMat );
};

#endif // MYVIDEOCAPTURE_H
