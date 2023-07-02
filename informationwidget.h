#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H
#include<QWidget>
#include<QTimer>
#include<QLabel>
#include<QMovie>
#include<QHBoxLayout>
#include<QMenu>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<list>
using namespace std;
class InformationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InformationWidget(QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QTimer *button_timer=new QTimer();
    QHBoxLayout *Layout=new QHBoxLayout;
    QLabel *button_back=new QLabel(this);
    QMovie *button_back_movie=new QMovie;
    QLabel *button_next=new QLabel(this);
    QMovie *button_next_movie=new QMovie;
    QLabel *button_start_or_stop=new QLabel(this);
    QMovie *button_start_or_stop_movie=new QMovie;
    QLabel *the_setting_call=new QLabel(this);
    QImage *setting_call_image=new QImage(":/image/image/icon.png");
    QCursor *mouse=new QCursor();
    QMenu *menu=new QMenu(this);
    QAction *open_music=new QAction(tr("打开"),this);
    QAction *save_main=new QAction(tr("存储"),this);
    QAction *load_main=new QAction(tr("读取"),this);
    QStringList play_files;
    QStringList play_files_simple;
    bool already_start=false;
    bool on_left_mouse=false;
    bool on_right_mouse=false;
    bool can_popup=false;
    bool can_clone=false;
    bool next_music=false;
    bool back_music=false;
    bool already_start_this=false;
    bool main_save=false;
    bool main_load=false;
public slots:
    void timer_of_button();
    void set_movie();
};
#endif // INFORMATIONWIDGET_H
