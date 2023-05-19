#include "resizablebutton.h"

ResizableButton::ResizableButton(QWidget *parent) : QPushButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("ResizableButton { border: none; }");
    m_anim = new QPropertyAnimation(this, "geometry", this);
    m_anim->setDuration(100);
}

void ResizableButton::enterEvent(QEvent *event) {
    m_anim->setStartValue(geometry());
    QRect target = geometry().adjusted(-10, -10, 10, 10);
    m_anim->setEndValue(target);
    m_anim->start(QPropertyAnimation::DeleteWhenStopped);
    QPushButton::enterEvent(event);
}

void ResizableButton::leaveEvent(QEvent *event) {
    m_anim->setStartValue(geometry());
    QRect target = geometry().adjusted(10, 10, -10, -10);
    m_anim->setEndValue(target);
    m_anim->start(QPropertyAnimation::DeleteWhenStopped);
    QPushButton::leaveEvent(event);
}
