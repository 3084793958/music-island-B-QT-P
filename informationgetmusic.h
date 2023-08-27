#ifndef INFORMATIONGETMUSIC_H
#define INFORMATIONGETMUSIC_H
#include<QtWidgets>
#include<QMediaPlayer>
#include<QNetworkAccessManager>
#include<QNetworkReply>
using namespace std;
class InformationGetmusic:public QWidget
{
    Q_OBJECT
public:
    explicit InformationGetmusic(QWidget *parent = nullptr);
    bool can_get_music_to_list=false;
    QString launch_file_name;
    QString launch_file_name_all;
    QMediaPlayer *try_to_listen=new QMediaPlayer();
    bool doing_getting=false;
    QLabel *name=new QLabel(tr("music island试听"),this);
    QLabel *setvolume=new QLabel(tr("设置音量\n100%"),this);
    QSlider *set_volume_main=new QSlider(Qt::Horizontal,this);
    QLabel *setmusic_time=new QLabel(tr("进度条\n00:00"),this);
    QSlider *set_music_time_main=new QSlider(Qt::Horizontal,this);
    QLabel *setmusic_speed=new QLabel(tr("速度\n100%"),this);
    QSlider *set_music_speed_main=new QSlider(Qt::Horizontal,this);
    int now_music_long=0;
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkAccessManager *manager_lyric=new QNetworkAccessManager(this);
    QMap<QString,QString> name_to_filesname;
    QPushButton *try_to_listen_button_play=new QPushButton(tr("播放"),this);
    QPushButton *try_to_listen_button_pause=new QPushButton(tr("暂停"),this);
    QListView *show_reply_music=new QListView(this);
    QStringList reply_music_list;
    QMap<QString,QUrl> reply_music_to_url;
    QList<int> get_music_id;
    QStringListModel *listmodel=new QStringListModel();
    QPushButton *get_it_button=new QPushButton(tr("选中"),this);
    QPushButton *do_not_get_button=new QPushButton(tr("取消"),this);
    QPushButton *up_page=new QPushButton(tr("上"),this);
    QPushButton *down_page=new QPushButton(tr("下"),this);
    QTimer *button_timer=new QTimer();
    QPushButton *only_music=new QPushButton(tr("仅音乐"),this);
    QPushButton *only_lyric=new QPushButton(tr("配置歌词"),this);
    int get_music_way=0;
    QString find_lyric_use_name=nullptr;
    int page=0;
    QString s_music_name;
    int time,h,m,s;
    bool HS_time_moving=false;
    int number_help=100;
public slots:
    void timer_of_button();
    void qslider_doing(int value);
    void music_value_doing(int value);
    void music_value_speed(int value);
    QString get_music_main(QString s_music_name,int page);
    void getting_music(QNetworkReply *reply);
    void getting_lyric(QNetworkReply *reply);
    void try_to_listen_button_play_click();
    void try_to_listen_button_pause_click();
    void get_it_button_click();
    void do_not_get_button_click();
    void up_page_button_click();
    void down_page_button_click();
    void only_music_click();
    void only_lyric_click();
};
#endif // INFORMATIONGETMUSIC_H
