#ifndef INFORMATIONPOPUP_H
#define INFORMATIONPOPUP_H
#include<QWidget>
#include<QLabel>
#include<QSlider>
#include<QTimer>
#include<QPushButton>
#include<QInputDialog>
#include<QMenu>
#include<QContextMenuEvent>
#include<QListView>
#include<QStringListModel>
using namespace std;
class InformationPopup : public QWidget
{
    Q_OBJECT
public:
    explicit InformationPopup(QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    QLabel *name=new QLabel(tr("music island控制"),this);
    QLabel *setvolume=new QLabel(tr("设置音量\n100%"),this);
    QSlider *set_volume_main=new QSlider(Qt::Horizontal,this);
    QLabel *setmusic_time=new QLabel(tr("进度条\n00:00"),this);
    QSlider *set_music_time_main=new QSlider(Qt::Horizontal,this);
    QLabel *setmusic_speed=new QLabel(tr("速度\n100%"),this);
    QSlider *set_music_speed_main=new QSlider(Qt::Horizontal,this);
    QPushButton *get_music_button=new QPushButton(tr("下载"),this);
    QLabel *get_music_text=new QLabel(this);
    QLabel *show_lyric=new QLabel(this);
    QLabel *show_lyric_next=new QLabel(this);
    QInputDialog *getting_music=new QInputDialog(this);
    QMenu *menu=new QMenu(this);
    QMenu *playing_way=new QMenu(tr("播放方式"),this);
    QAction *action_all=new QAction(tr("循环播放"),this);
    QAction *action_this=new QAction(tr("单曲循环"),this);
    QAction *action_random=new QAction(tr("随机播放"),this);
    QAction *action_math_way=new QAction(tr("函数播放法"),this);
    QAction *action_clean=new QAction(tr("清空列表"),this);
    QMenu *lyric_way=new QMenu(tr("外部歌词"),this);
    QAction *lyric_show=new QAction(tr("显示"),this);
    QAction *lyric_hide=new QAction(tr("隐藏"),this);
    QAction *lyric_move=new QAction(tr("躲避鼠标"),this);
    QAction *action_set_lyric_font=new QAction(tr("设置字体颜色"),this);
    QAction *action_set_back_color=new QAction(tr("设置背景颜色"),this);
    int the_way_of_lyric=2;
    QListView *show_music=new QListView(this);
    QStringList play_files;
    QStringListModel *listmodel=new QStringListModel();
    int now_music_long;
    QString now_music_name;
    int now_playing=0;
    int the_way_of_playing=1;
    int size_x_this=200;
    bool change=false;
    int p;
    int q;
    int n;
    int b;
    bool clean_all=false;
    bool QS_music_long_move=false;
    QMenu *Qlist_menu=new QMenu(this);
    QAction *move_up=new QAction(tr("上移"),this);
    QAction *move_down=new QAction(tr("下移"),this);
    QAction *move_out=new QAction(tr("移出列表"),this);
    QAction *del_file=new QAction(tr("删除文件"),this);
    bool up_this=false;
    bool down_this=false;
    bool out_this=false;
    bool del_this=false;
    bool start_get=false;
    bool set_lyric_font=false;
    bool set_back_color=false;
public slots:
    void qslider_doing(int value);
    void music_value_doing(int value);
    void music_value_speed(int value);
    void get_music_on();
};

#endif // INFORMATIONPOPUP_H
