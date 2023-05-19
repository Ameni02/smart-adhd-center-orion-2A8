#include "QDebug"
#include "sidebar.h"

Sidebar::Sidebar(QFrame *frame) : animation(new QPropertyAnimation(frame, "geometry")), frame(frame)
{
    // Set up the animation
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // Set the initial position of the sidebar
  //  frame->move(-230, 7);
    show();
}
void Sidebar::show() {
    // Move the sidebar to its shown position
    frame->move(-230, 10);
}

void Sidebar::hide() {
    // Move the sidebar all the way to the left, so it is hidden
    frame->move(20, 10);
}
void Sidebar::toggleSidebar() {
    // Check if the sidebar is currently shown or hidden
    if (frame->x() == 20) {
        // If the sidebar is currently shown, hide it by moving it to the left
        animation->setStartValue(QRect(20, 10, frame->width(), frame->height()));
        animation->setEndValue(QRect(-230, 10, frame->width(), frame->height()));
        connect(animation, &QPropertyAnimation::stateChanged, this, [this](){
            if (frame->x() == -frame->width()) {
                isSidebarShown = false;
            }
        });
        animation->start();
    } else {
        // If the sidebar is currently hidden, show it by moving it to the right
        animation->setStartValue(QRect(-230, 10, frame->width(), frame->height()));
        animation->setEndValue(QRect(20, 10, frame->width(), frame->height()));
        connect(animation, &QPropertyAnimation::stateChanged, this, [this](){
            if (frame->x() == 20) {
                isSidebarShown = true;
            }
        });
        animation->start();
    }
}

