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
#include<informationlyric.h>
#include<QMouseEvent>
#include<informationgetmusic.h>
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
    InformationLyric *lyric_show=new InformationLyric;
    InformationGetmusic *getting_music_widget=new InformationGetmusic;
    QMenu *menu=new QMenu(this);
    QAction *open_music=new QAction(tr("打开"),this);
    QAction *save_main=new QAction(tr("存储"),this);
    QAction *load_main=new QAction(tr("读取"),this);
    QAction *set_font=new QAction(tr("设置字体"),this);
    QAction *set_color=new QAction(tr("设置颜色"),this);
    QMenu *choose_size=new QMenu(tr("设置按钮大小"),this);
    QAction *top_panel=new QAction(tr("dde-top-panel"),this);
    QAction *dock=new QAction(tr("dde-dock"),this);
    QMenu *pos_dock=new QMenu(tr("位置"),this);
    QAction *pos_up_down=new QAction(tr("上下"),this);
    QAction *pos_left_right=new QAction(tr("左右"),this);
    QStringList play_files;
    QStringList play_files_simple;
    bool already_start=false;
    bool on_left_mouse=false;
    bool on_right_mouse=false;
    bool can_popup=true;
    bool can_clone=false;
    bool next_music=false;
    bool back_music=false;
    bool already_start_this=false;
    bool main_save=false;
    bool main_load=false;
    bool color_setting=false;
    bool font_setting=false;
    bool can_not_use=false;
    int the_way_of_choose_type=1;
    int the_way_of_choose_pos=1;
    bool change_pos=false;
    QLabel *lyric_main_1=new QLabel(lyric_show);
    QLabel *lyric_main_2=new QLabel(lyric_show);
    QLabel *show_name=new QLabel(lyric_show);
public slots:
    void timer_of_button();
};
#endif // INFORMATIONWIDGET_H
