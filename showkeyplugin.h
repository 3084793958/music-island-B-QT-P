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
    int time,h,m,s;
    int load_time;
    int now_time_help;
    int all_time_help;
    bool first_time=true;
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkAccessManager *manager2=new QNetworkAccessManager(this);
    QByteArray get_reply;
    QList<int> get_music_id;
    QList<QString> get_music_name;
    QList<QString> get_music_name_and_id;
    QString files_name,files_name_all;
    int wait_time=0;
    bool first_try_time=true;
public slots:
    void timer_update();
    void getting_music(QNetworkReply *reply);
private:
    InformationWidget *m_pluginWidget;
    QLabel *m_tipsWidget;
    InformationPopup *m_popupWidget;
};

#endif // SHOWKEYPLUGIN_H
