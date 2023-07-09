#ifndef INFORMATIONLYRIC_H
#define INFORMATIONLYRIC_H
#include<QWidget>
#include<QTimer>
#include<QLabel>
using namespace std;
class InformationLyric:public QWidget
{
    Q_OBJECT
public:
    explicit InformationLyric(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int mouse_pos_x;
    int mouse_pos_y;
    bool left_mouse;
    bool lyric_can_move=true;
    bool down_to_up=true;
    QCursor *mouse=new QCursor();
    QTimer *button_timer=new QTimer();
public slots:
    void timer_of_button();
};

#endif // INFORMATIONLYRIC_H
