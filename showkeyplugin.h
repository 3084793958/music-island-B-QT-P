#ifndef SHOWKEYPLUGIN_H
#define SHOWKEYPLUGIN_H

#include<dde-dock/pluginsiteminterface.h>
#include<QObject>
#include<informationwidget.h>
#include<informationpopup.h>
#include<QMediaPlayer>
#include<QNetworkAccessManager>
#include<QNetworkReply>
class ShowKeyPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "music-island.json")
public:
    explicit ShowKeyPlugin(QObject *parent = nullptr);
    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    const QString pluginDisplayName() const override;
    QWidget *itemPopupApplet(const QString &itemKey) override;
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;
    QTimer *update_timer=new QTimer;
    QMediaPlayer *play_main=new QMediaPlayer();
    QMediaPlayer *try_play=new QMediaPlayer();
    bool not_do_anything=false;
    int number_help=100;
    int time,h,m,s,time_all,time_h,time_m,time_s;
    int load_time;
    int now_time_help;
    int all_time_help;
    bool first_time=true;
    bool out_thing=false;
    bool first_try_time=true;
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkAccessManager *manager2=new QNetworkAccessManager(this);
    QNetworkAccessManager *manager_lyric=new QNetworkAccessManager(this);
    QByteArray get_reply;
    QByteArray get_reply_lyric;
    QList<int> get_music_id;
    QList<QString> get_music_name;
    QList<QString> get_music_name_and_id;
    QString files_name,files_name_all;
    QList<QString> lyric_text;
    QList<int> lyric_time;
    QColor color;
    QFont font;
    QFont lyric_font;
    QColor lyric_color;
    int wait_time=0;
    int music_id;
    int lyricsID=0;
    string lyric_main;
    bool change_change=false;
    bool can_load=false;
    QColor back_color;
    QString get_artists;
public slots:
    void timer_update();
    void getting_music(QNetworkReply *reply);
    void getting_lyric(QNetworkReply *reply);
private:
    InformationWidget *m_pluginWidget;
    QLabel *m_tipsWidget;
    InformationPopup *m_popupWidget;
};

#endif // SHOWKEYPLUGIN_H
