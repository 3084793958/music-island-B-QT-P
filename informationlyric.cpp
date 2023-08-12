#include<QMouseEvent>
#include<QGuiApplication>
#include<QScreen>
#include "informationlyric.h"
using namespace std;
void InformationLyric::timer_of_button()
{
    if (lyric_can_move==false&&width()!=0&&mouse->pos().x()-pos().x()>=0&&mouse->pos().x()-pos().x()<=700&&mouse->pos().y()-pos().y()>=0&&mouse->pos().y()-pos().y()<=90)
    {
        if (down_to_up)
        {
            down_to_up=false;
            QRect screenRect = QGuiApplication::primaryScreen()->geometry();
            move(screenRect.width()/2-350,screenRect.height()-175);
        }
        else
        {
            down_to_up=true;
            QRect screenRect = QGuiApplication::primaryScreen()->geometry();
            move(screenRect.width()/2-350,175);
        }
    }
}
InformationLyric::InformationLyric(QWidget *parent)
    :QWidget(parent)
{
    setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(false);
    button_timer->setInterval(30);
    connect(button_timer,SIGNAL(timeout()),this,SLOT(timer_of_button()));
    button_timer->start();
    only_look->setText(nullptr);
    only_look->move(0,0);
    only_look->resize(700,90);
    only_look->setStyleSheet(QString("background:rgba(%1,%2,%3,%4)").arg(255).arg(255).arg(255).arg(10));
    only_look->lower();
    only_look->setEnabled(false);
}
void InformationLyric::mousePressEvent(QMouseEvent *event)
{
    if (lyric_can_move)
    {
        if(event->buttons() == Qt::LeftButton)
        {
            left_mouse = true;
        }
        else
        {
            left_mouse = false;
        }
        mouse_pos_x = event->globalPos().x()-pos().x();
        mouse_pos_y = event->globalPos().y()-pos().y();
        event->accept();
    }
}
void InformationLyric::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}
void InformationLyric::mouseMoveEvent(QMouseEvent *event)
{
    if ((Qt::LeftButton)and(left_mouse)and(lyric_can_move))
    {
        setCursor(QCursor(Qt::OpenHandCursor));
        move(event->globalPos().x()-mouse_pos_x,event->globalPos().y()-mouse_pos_y);
        event->accept();
    }
}
