#ifndef SHOWKEYPLUGIN_H
#define SHOWKEYPLUGIN_H

#include <interfaces/pluginsiteminterface.h>
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
    ~ShowKeyPlugin() override;
    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    const QString pluginDisplayName() const override;
    QWidget *itemPopupApplet(const QString &itemKey) override;
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;
    //for Easy_Desktop
    bool pluginIsAllowUnload() override;
    void pluginUnload() override;
    void pluginGetCarrierQMenu(Carrier_Type carrier_type, QMenu *menu, P_Sender * const action_sender) override;
    QSize pluginSetWidgetSize(Carrier_Type carrier_type, bool *isValid) override;
    void pluginGetIsMouseInPluginCarrier(Carrier_Type carrier_type, bool result) override;
    void pluginGetSender(P_Sender * const update_sender, P_Sender * const send_data_sender) override;
    bool pluginSetShowCarrierCloseButton(Carrier_Type carrier_type, bool *isValid) override;
    P_Sender *m_update_sender = nullptr;
    //for Easy_Desktop
    QTimer *update_timer=new QTimer(this);
    QMediaPlayer *play_main=new QMediaPlayer(this);
    bool not_do_anything=false;
    int number_help=100;
    int time,h,m,s,time_all,time_h,time_m,time_s;
    int load_time;
    int now_time_help;
    int all_time_help;
    bool first_time=true;
    bool out_thing=false;
    QList<QString> lyric_text;
    QList<int> lyric_time;
    QColor color;
    QFont font;
    QFont lyric_font;
    QColor lyric_color;
    int music_id;
    int lyricsID=0;
    string lyric_main;
    bool change_change=false;
    bool can_load=false;
    QColor back_color;
    QString get_artists;
    QTimer *to_do_timer=new QTimer(this);
    QTimer *to_find_lyric=new QTimer(this);
public slots:
    void timer_update();
    void timer_to_do();
    void find_lyric_timer();
private:
    InformationWidget *m_pluginWidget;
    QLabel *m_tipsWidget;
    InformationPopup *m_popupWidget;
public:
    void load();
    void save();
    void color_setting();
    void font_setting();
    void disable_plugin();
};

#endif // SHOWKEYPLUGIN_H
