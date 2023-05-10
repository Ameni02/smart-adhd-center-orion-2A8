#ifndef RESIZABLEBUTTON_H
#define RESIZABLEBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class ResizableButton : public QPushButton {
public:
    ResizableButton(QWidget *parent = nullptr);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
protected:


private:
    QPropertyAnimation *m_anim;
};

#endif // RESIZABLEBUTTON_H
