#include "showkeyplugin.h"
#include<QListView>
#include<QMessageBox>
#include<unistd.h>
#include<fstream>
#include<QFontDialog>
#include<QColorDialog>
#include<QRgba64>
int getRand(int min,int max);
int getRand(int min,int max)
{
    return (rand()%(max-min+1))+min;
}
ShowKeyPlugin::ShowKeyPlugin(QObject *parent)
    : QObject(parent)
{
    update_timer->setInterval(30);
    connect(update_timer,SIGNAL(timeout()),this,SLOT(timer_update()));
    update_timer->start();
    connect(play_main,&QMediaPlayer::stateChanged,[=]()
    {
            switch(play_main->state())
            {
            case QMediaPlayer::StoppedState:
            {
                lyricsID=0;
                if ((((!not_do_anything)or(first_time==true&&play_main->position()==play_main->duration()))and(!out_thing)and(!change_change))or(play_main->position()==play_main->duration()))
                {
                    first_time=false;
                    not_do_anything=false;
                    change_change=false;
                if (m_popupWidget->the_way_of_playing==2)
                {
                    number_help=-5;
                    play_main->play();
                }
                if (m_popupWidget->the_way_of_playing==1)
                {
                    if (m_popupWidget->now_playing==m_pluginWidget->play_files_simple.size()-1)
                    {
                        QModelIndex index=m_popupWidget->listmodel->index(0);
                        m_popupWidget->now_playing=0;
                        m_popupWidget->show_music->setCurrentIndex(index);
                        m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
                        play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                        number_help=-5;
                        play_main->play();
                    }
                    else
                    {
                        QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing+1);
                        m_popupWidget->now_playing++;
                        m_popupWidget->show_music->setCurrentIndex(index);
                        m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
                        play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                        number_help=-5;
                        play_main->play();
                    }
                }
                if (m_popupWidget->the_way_of_playing==3)
                {
                    int random_number=getRand(0,m_pluginWidget->play_files_simple.size()-1);
                    QModelIndex index=m_popupWidget->listmodel->index(random_number);
                    m_popupWidget->now_playing=random_number;
                    m_popupWidget->show_music->setCurrentIndex(index);
                    m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
                    play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                    number_help=-5;
                    play_main->play();
                }
                if (m_popupWidget->the_way_of_playing==4)
                {
                    if (m_popupWidget->q==0)
                    {
                        m_popupWidget->q=1;
                    }
                    int last_number=int((double(m_popupWidget->p)/m_popupWidget->q)*pow(m_popupWidget->now_playing,m_popupWidget->n)+m_popupWidget->b);
                    if (last_number<0)
                    {
                        last_number=0;
                    }
                    if (last_number>m_pluginWidget->play_files_simple.size()-1)
                    {
                        last_number=m_pluginWidget->play_files_simple.size()-1;
                    }
                    QModelIndex index=m_popupWidget->listmodel->index(last_number);
                    m_popupWidget->now_playing=last_number;
                    m_popupWidget->show_music->setCurrentIndex(index);
                    m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
                    play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                    m_pluginWidget->already_start=true;
                    number_help=-5;
                    play_main->play();
                }
                }
                else
                {
                    not_do_anything=false;
                }
                if (out_thing)
                {
                    out_thing=false;
                }
                if (change_change)
                {
                    change_change=false;
                }
                lyricsID=0;
                QString files_url=m_pluginWidget->play_files[m_popupWidget->now_playing];
                files_url.chop(3);
                files_url.append("lrc");
                QFile file(files_url);
                lyric_time.clear();
                lyric_text.clear();
                m_popupWidget->show_lyric->setText("");
                m_popupWidget->show_lyric_next->setText("");
                m_pluginWidget->lyric_main_1->setText("");
                m_pluginWidget->lyric_main_2->setText("");
                if (file.open(QIODevice::ReadOnly|QIODevice::Text))
                {
                    ifstream load_data;
                    load_data.open(files_url.toStdString(),ios::in);
                    string s;
                    QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
                    while(getline(load_data,s))
                    {
                        int index = 0;
                        QRegularExpressionMatch match;
                        match = regularExpression.match(QString::fromStdString(s),index);
                        if(match.hasMatch())
                        {
                            int totalTime = match.captured(1).toInt() * 60000 + match.captured(2).toInt() * 1000;
                            QString currentText =QString::fromStdString(match.captured(4).toStdString());
                            lyric_text.push_back(currentText);
                            lyric_time.push_back(totalTime);
                        }
                    }
                }
                else
                {
                    m_popupWidget->show_lyric->setText("无歌词");
                    m_popupWidget->show_lyric_next->setText("");
                    m_pluginWidget->lyric_main_1->setText("无歌词");
                    m_pluginWidget->lyric_main_2->setText("");
                }
                break;
            }
            case QMediaPlayer::PlayingState:
            {
                if (play_main->position()==0)
                {
                lyricsID=0;
                QString files_url=m_pluginWidget->play_files[m_popupWidget->now_playing];
                files_url.chop(3);
                files_url.append("lrc");
                QFile file(files_url);
                lyric_time.clear();
                lyric_text.clear();
                m_popupWidget->show_lyric->setText("");
                m_popupWidget->show_lyric_next->setText("");
                m_pluginWidget->lyric_main_1->setText("");
                m_pluginWidget->lyric_main_2->setText("");
                if (file.open(QIODevice::ReadOnly|QIODevice::Text))
                {
                    ifstream load_data;
                    load_data.open(files_url.toStdString(),ios::in);
                    string s;
                    QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
                    while(getline(load_data,s))
                    {
                        int index = 0;
                        QRegularExpressionMatch match;
                        match = regularExpression.match(QString::fromStdString(s),index);
                        if(match.hasMatch())
                        {
                            int totalTime = match.captured(1).toInt() * 60000 + match.captured(2).toInt() * 1000;
                            QString currentText =QString::fromStdString(match.captured(4).toStdString());
                            lyric_text.push_back(currentText);
                            lyric_time.push_back(totalTime);
                        }
                    }
                }
                else
                {
                    m_popupWidget->show_lyric->setText("无歌词");
                    m_popupWidget->show_lyric_next->setText("");
                    m_pluginWidget->lyric_main_1->setText("无歌词");
                    m_pluginWidget->lyric_main_2->setText("");
                }
            }
            }
            case QMediaPlayer::PausedState:
            {
                ;//L'Internationale Sera le genre humain.
            }
            }
    });
}
const QString ShowKeyPlugin::pluginName() const
{
    return QStringLiteral("Music_island");
}
const QString ShowKeyPlugin::pluginDisplayName() const
{
    return QString("Music island");
}
void ShowKeyPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter=proxyInter;
    m_pluginWidget=new InformationWidget;
    m_tipsWidget=new QLabel;
    m_popupWidget=new InformationPopup;
    if (!pluginIsDisable())
    {
    m_proxyInter->itemAdded(this,pluginName());
    }
    load_time=-1;
    system("mkdir ~/.local/lib/music-island-c++p;touch ~/.local/lib/music-island-c++p/data.txt;touch ~/.local/lib/music-island-c++p/data2.txt");
    string files_name=getenv("HOME")+string("/.local/lib/music-island-c++p/data.txt");
    string files_name2=getenv("HOME")+string("/.local/lib/music-island-c++p/data2.txt");
    ifstream load_data;
    load_data.open(files_name,ios::in);
    string s;
    m_pluginWidget->already_start=false;
    m_popupWidget->now_music_name=nullptr;
    not_do_anything=true;
    play_main->stop();
    m_popupWidget->now_playing=0;
    m_pluginWidget->play_files_simple.clear();
    m_pluginWidget->play_files.clear();
    m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
    m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
    m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
    m_popupWidget->show_music->setSpacing(0);
    while(getline(load_data,s))
    {
        load_time++;
        if (load_time==1)
        {
            m_popupWidget->set_volume_main->setValue(atoi(s.c_str()));
        }
        if (load_time==2)
        {
            now_time_help=(atoi(s.c_str()));
        }
        if (load_time==3)
        {
            all_time_help=(atoi(s.c_str()));
        }
        if (load_time==4)
        {
            m_popupWidget->set_music_speed_main->setValue(atoi(s.c_str()));
        }
        if (load_time==5)
        {
            m_popupWidget->now_playing=QString::fromStdString(s).toInt();
        }
        if (load_time==6)
        {
            m_popupWidget->the_way_of_playing=(atoi(s.c_str()));
            if (m_popupWidget->the_way_of_playing==1)
            {
                m_popupWidget->action_all->setIconVisibleInMenu(true);
                m_popupWidget->action_this->setIconVisibleInMenu(false);
                m_popupWidget->action_random->setIconVisibleInMenu(false);
                m_popupWidget->action_math_way->setIconVisibleInMenu(false);
            }
            if (m_popupWidget->the_way_of_playing==2)
            {
                m_popupWidget->action_all->setIconVisibleInMenu(false);
                m_popupWidget->action_this->setIconVisibleInMenu(true);
                m_popupWidget->action_random->setIconVisibleInMenu(false);
                m_popupWidget->action_math_way->setIconVisibleInMenu(false);
            }
            if (m_popupWidget->the_way_of_playing==3)
            {
                m_popupWidget->action_all->setIconVisibleInMenu(false);
                m_popupWidget->action_this->setIconVisibleInMenu(false);
                m_popupWidget->action_random->setIconVisibleInMenu(true);
                m_popupWidget->action_math_way->setIconVisibleInMenu(false);
            }
            if (m_popupWidget->the_way_of_playing==4)
            {
                m_popupWidget->action_all->setIconVisibleInMenu(false);
                m_popupWidget->action_this->setIconVisibleInMenu(false);
                m_popupWidget->action_random->setIconVisibleInMenu(false);
                m_popupWidget->action_math_way->setIconVisibleInMenu(true);
            }
        }
        if (load_time==7)
        {
            m_popupWidget->p=(atoi(s.c_str()));
        }
        if (load_time==8)
        {
            m_popupWidget->q=(atoi(s.c_str()));
        }
        if (load_time==9)
        {
            m_popupWidget->n=(atoi(s.c_str()));
        }
        if (load_time==10)
        {
            m_popupWidget->b=(atoi(s.c_str()));
        }
        if (load_time>10)
        {
            m_pluginWidget->play_files.append(QString::fromStdString(s));
            QUrl url(QString::fromStdString(s));
            m_pluginWidget->play_files_simple.append(url.fileName());
        }
    }
    load_data.close();
    if (load_time>10)
    {
        not_do_anything=true;
        m_pluginWidget->already_start=false;
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
        m_popupWidget->show_music->setCurrentIndex(index);
        m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
        m_popupWidget->now_playing = m_popupWidget->show_music->currentIndex().row();
        play_main->setPosition(int(float(now_time_help)/100*all_time_help));
        can_load=true;
    }
    load_data.open(files_name2,ios::in);
    load_time=-1;
    while(getline(load_data,s))
    {
        load_time++;
        if (load_time==1)
        {
            font=QString::fromStdString(s);
        }
        if (load_time==2)
        {
            color.setNamedColor(QString::fromStdString(s));
        }
        if (load_time==3)
        {
            m_popupWidget->the_way_of_lyric=QString::fromStdString(s).toInt();
        }
        if (load_time==4)
        {
            lyric_font=QString::fromStdString(s);
        }
        if (load_time==5)
        {
            lyric_color.setNamedColor(QString::fromStdString(s));
        }
        if (load_time==6)
        {
            m_pluginWidget->the_way_of_choose_type=QString::fromStdString(s).toInt();
            if (m_pluginWidget->the_way_of_choose_type==1)
            {
                m_pluginWidget->button_start_or_stop_movie->setScaledSize(QSize(23, 23));
                m_pluginWidget->top_panel->setIconVisibleInMenu(true);
                m_pluginWidget->dock->setIconVisibleInMenu(false);
            }
            if (m_pluginWidget->the_way_of_choose_type==2)
            {
                m_pluginWidget->button_start_or_stop_movie->setScaledSize(QSize(20, 20));
                m_pluginWidget->top_panel->setIconVisibleInMenu(false);
                m_pluginWidget->dock->setIconVisibleInMenu(true);
            }
        }
        if (load_time==7)
        {
            back_color.setRed(QString::fromStdString(s).toInt());
        }
        if (load_time==8)
        {
            back_color.setGreen(QString::fromStdString(s).toInt());
        }
        if (load_time==9)
        {
            back_color.setBlue(QString::fromStdString(s).toInt());
        }
        if (load_time==10)
        {
            back_color.setAlpha(QString::fromStdString(s).toInt());
            m_pluginWidget->lyric_show->only_look->setStyleSheet(QString("background:rgba(%1,%2,%3,%4)").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()).arg(back_color.alpha()));
        }
        if (load_time==11)
        {
            m_pluginWidget->the_way_of_choose_pos=QString::fromStdString(s).toInt();
            if (m_pluginWidget->the_way_of_choose_pos==1)
            {
                m_pluginWidget->pos_up_down->setIconVisibleInMenu(true);
                m_pluginWidget->pos_left_right->setIconVisibleInMenu(false);
                m_pluginWidget->Layout->setDirection(QBoxLayout::LeftToRight);
                m_pluginWidget->setLayout(m_pluginWidget->Layout);
            }
            if (m_pluginWidget->the_way_of_choose_pos==2)
            {
                m_pluginWidget->pos_up_down->setIconVisibleInMenu(false);
                m_pluginWidget->pos_left_right->setIconVisibleInMenu(true);
                m_pluginWidget->Layout->setDirection(QBoxLayout::Down);
                m_pluginWidget->setLayout(m_pluginWidget->Layout);
            }
        }
        if (load_time==12)
        {
            m_pluginWidget->getting_music_widget->set_volume_main->setValue(QString::fromStdString(s).toInt());
        }
        if (load_time==13)
        {
            m_pluginWidget->getting_music_widget->set_music_time_main->setValue(QString::fromStdString(s).toInt());
        }
        if (load_time==14)
        {
            m_pluginWidget->getting_music_widget->set_music_speed_main->setValue(QString::fromStdString(s).toInt());
        }
    }
    load_data.close();
    if (load_time>=1)
    {
    m_popupWidget->name->setFont(font);
    m_popupWidget->setvolume->setFont(font);
    m_popupWidget->set_volume_main->setFont(font);
    m_popupWidget->setmusic_time->setFont(font);
    m_popupWidget->set_music_time_main->setFont(font);
    m_popupWidget->setmusic_speed->setFont(font);
    m_popupWidget->set_music_speed_main->setFont(font);
    m_popupWidget->get_music_button->setFont(font);
    m_popupWidget->get_music_text->setFont(font);
    m_popupWidget->getting_music->setFont(font);
    m_popupWidget->show_music->setFont(font);
    m_popupWidget->show_lyric->setFont(font);
    m_popupWidget->show_lyric_next->setFont(font);
    m_tipsWidget->setFont(font);
    m_pluginWidget->show_name->setFont(font);
    }
    if (load_time>=4)
    {
    m_pluginWidget->lyric_main_1->setFont(lyric_font);
    m_pluginWidget->lyric_main_2->setFont(lyric_font);
    }
    if (load_time>=2)
    {
    m_popupWidget->name->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->setvolume->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->set_volume_main->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->setmusic_time->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->set_music_time_main->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->setmusic_speed->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->set_music_speed_main->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->get_music_button->setStyleSheet(QString("QPushButton{background:rgba(0,0,0,10);color:%1}"
                                                           "QPushButton:hover{background:rgba(0,0,0,25);color:%1}").arg(color.name()));
    m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                     "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                     "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
    m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
    m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
    m_pluginWidget->show_name->setStyleSheet(QString("color:%1").arg(color.name()));
    }
    if (load_time>=5)
    {
    m_pluginWidget->lyric_main_1->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
    m_pluginWidget->lyric_main_2->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
    }
    if(load_time>=3)
    {
    if (m_popupWidget->the_way_of_lyric==1)
    {
        m_popupWidget->lyric_show->setIconVisibleInMenu(true);
        m_popupWidget->lyric_hide->setIconVisibleInMenu(false);
        m_popupWidget->lyric_move->setIconVisibleInMenu(false);
        }
    if (m_popupWidget->the_way_of_lyric==2)
    {
        m_popupWidget->lyric_show->setIconVisibleInMenu(false);
        m_popupWidget->lyric_hide->setIconVisibleInMenu(true);
        m_popupWidget->lyric_move->setIconVisibleInMenu(false);
    }
    if (m_popupWidget->the_way_of_lyric==3)
    {
        m_popupWidget->lyric_show->setIconVisibleInMenu(false);
        m_popupWidget->lyric_hide->setIconVisibleInMenu(false);
        m_popupWidget->lyric_move->setIconVisibleInMenu(true);
    }
    }
    if (can_load)
    {
    lyricsID=0;
    QString files_url=m_pluginWidget->play_files[m_popupWidget->now_playing];
    files_url.chop(3);
    files_url.append("lrc");
    QFile file(files_url);
    lyric_time.clear();
    lyric_text.clear();
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ifstream load_data;
        load_data.open(files_url.toStdString(),ios::in);
        string s;
        QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
        while(getline(load_data,s))
        {
            int index = 0;
            QRegularExpressionMatch match;
            match = regularExpression.match(QString::fromStdString(s),index);
            if(match.hasMatch())
            {
                int totalTime = match.captured(1).toInt() * 60000 + match.captured(2).toInt() * 1000;
                QString currentText =QString::fromStdString(match.captured(4).toStdString());
                lyric_text.push_back(currentText);
                lyric_time.push_back(totalTime);
            }
        }
    }
    else
    {
        m_popupWidget->show_lyric->setText("无歌词");
        m_popupWidget->show_lyric_next->setText("");
        m_pluginWidget->lyric_main_1->setText("无歌词");
        m_pluginWidget->lyric_main_2->setText("");
    }
    }
}
QWidget *ShowKeyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_pluginWidget;
}
bool ShowKeyPlugin::pluginIsAllowDisable()
{
    return true;
}
bool ShowKeyPlugin::pluginIsDisable()
{
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}
void ShowKeyPlugin::pluginStateSwitched()
{
    const bool disabledNew = !pluginIsDisable();
    m_proxyInter->saveValue(this, "disabled", disabledNew);
    if (disabledNew) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
}
QWidget *ShowKeyPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    if (m_pluginWidget->already_start==false)
    {
        m_tipsWidget->setText("music island");
    }
    else
    {
        m_tipsWidget->setText("正在播放:"+m_popupWidget->now_music_name);
    }
    return m_tipsWidget;
}
QWidget *ShowKeyPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    if (m_pluginWidget->can_popup)
    {
        if (m_popupWidget->size_x_this==200)
        {
            m_popupWidget->resize(200,180);
        }
        else
        {
            m_popupWidget->resize(500,210);
        }
        return m_popupWidget;
    }
    else
    {
        return nullptr;
    }
}
void ShowKeyPlugin::timer_update()
{
    if (m_pluginWidget->change_pos)
    {
        m_pluginWidget->change_pos=false;
        m_proxyInter->itemRemoved(this, pluginName());
        m_proxyInter->itemAdded(this, pluginName());
        m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                         "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                         "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
    }
    if (pluginIsDisable())
    {
        play_main->pause();
        m_pluginWidget->getting_music_widget->try_to_listen->pause();
        m_pluginWidget->getting_music_widget->doing_getting=false;
        m_pluginWidget->getting_music_widget->close();
        m_pluginWidget->already_start=false;
        m_popupWidget->lyric_show->setIconVisibleInMenu(false);
        m_popupWidget->lyric_hide->setIconVisibleInMenu(true);
        m_popupWidget->lyric_move->setIconVisibleInMenu(false);
        m_popupWidget->the_way_of_lyric=2;
        m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                         "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                         "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
    }
    if ((abs(number_help))==100)
    {
        play_main->setVolume(m_popupWidget->set_volume_main->value());
    }
    else
    {
        play_main->setVolume(abs(number_help));
    }
    if ((abs(number_help))<100)
    {
        number_help-=5;
    }
    if (number_help==0)
    {
        play_main->pause();
        number_help=-100;
    }
    play_main->setPlaybackRate(qreal(m_popupWidget->set_music_speed_main->value())/100);
    if (m_pluginWidget->can_clone)
    {
        m_pluginWidget->can_clone=false;
        not_do_anything=true;
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        if (!m_pluginWidget->already_start&&m_pluginWidget->play_files.size()<=1)
        {
            QModelIndex index=m_popupWidget->listmodel->index(0);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
        }
        else
        {
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
        if(play_main->position()==0&&!m_pluginWidget->already_start)
        {
        lyricsID=0;
        QString files_url=m_pluginWidget->play_files[m_popupWidget->now_playing];
        files_url.chop(3);
        files_url.append("lrc");
        QFile file(files_url);
        lyric_time.clear();
        lyric_text.clear();
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            ifstream load_data;
            load_data.open(files_url.toStdString(),ios::in);
            string s;
            QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
            while(getline(load_data,s))
            {
                int index = 0;
                QRegularExpressionMatch match;
                match = regularExpression.match(QString::fromStdString(s),index);
                if(match.hasMatch())
                {
                    int totalTime = match.captured(1).toInt() * 60000 + match.captured(2).toInt() * 1000;
                    QString currentText =QString::fromStdString(match.captured(4).toStdString());
                    lyric_text.push_back(currentText);
                    lyric_time.push_back(totalTime);
                }
            }
        }
        else
        {
            m_popupWidget->show_lyric->setText("无歌词");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("无歌词");
            m_pluginWidget->lyric_main_2->setText("");
        }
        }
    }
    if (m_pluginWidget->play_files_simple.empty())
    {
        m_popupWidget->size_x_this=200;
    }
    else
    {
        m_popupWidget->size_x_this=500;
    }
    if ((m_pluginWidget->back_music)and(m_popupWidget->now_music_name!=nullptr))
    {
        m_pluginWidget->back_music=false;
        if (m_popupWidget->now_playing==0)
        {
            not_do_anything=true;
            QModelIndex index=m_popupWidget->listmodel->index(m_pluginWidget->play_files_simple.size()-1);
            m_popupWidget->now_playing=m_pluginWidget->play_files_simple.size()-1;
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            change_change=true;
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
            if (m_pluginWidget->already_start)
            {
                number_help=-5;
                play_main->play();
            }
            else
            {
                number_help=95;
            }
        }
        else
        {
            not_do_anything=true;
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing-1);
            m_popupWidget->now_playing--;
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
            if (m_pluginWidget->already_start)
            {
                number_help=-5;
                play_main->play();
            }
            else
            {
                number_help=95;
            }
        }
    }
    if (m_pluginWidget->next_music && m_popupWidget->now_music_name!=nullptr)
    {
        m_pluginWidget->next_music=false;
        if (m_popupWidget->now_playing==m_pluginWidget->play_files_simple.size()-1)
        {
            not_do_anything=true;
            QModelIndex index=m_popupWidget->listmodel->index(0);
            m_popupWidget->now_playing=0;
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            change_change=true;
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
            if (m_pluginWidget->already_start)
            {
                number_help=-5;
                play_main->play();
            }
            else
            {
                number_help=95;
            }
        }
        else
        {
            not_do_anything=true;
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing+1);
            m_popupWidget->now_playing++;
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
            if (m_pluginWidget->already_start)
            {
                number_help=-5;
                play_main->play();
            }
            else
            { 
                number_help=95;
            }
        }
    }
    if (m_pluginWidget->already_start_this)
    {
        m_pluginWidget->already_start_this=false;
        if (m_pluginWidget->already_start)
        {
            number_help=-5;
            play_main->play();
        }
        else
        {
            number_help=95;
        }
    }
    if (m_popupWidget->change)
    {
        m_popupWidget->change=false;
        not_do_anything=true;
        m_popupWidget->now_playing = m_popupWidget->show_music->currentIndex().row();
        change_change=true;
        play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
        m_pluginWidget->already_start=true;
        number_help=-5;
        play_main->play();
    }
    if (m_popupWidget->clean_all)
    {
        out_thing=true;
        m_popupWidget->clean_all=false;
        m_pluginWidget->already_start=false;
        m_popupWidget->now_music_name=nullptr;
        not_do_anything=true;
        play_main->stop();
        m_popupWidget->now_playing=0;
        m_pluginWidget->play_files_simple.clear();
        m_pluginWidget->play_files.clear();
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        lyric_text.clear();
        lyric_time.clear();
        m_popupWidget->show_lyric->setText("");
        m_popupWidget->show_lyric_next->setText("");
        m_pluginWidget->lyric_main_1->setText("");
        m_pluginWidget->lyric_main_2->setText("");
    }
    if (m_popupWidget->out_this)
    {
        m_popupWidget->out_this=false;
        if (m_popupWidget->show_music->currentIndex().row()!=-1)
        {
        if (m_pluginWidget->play_files_simple.size()==1)
        {
            out_thing=true;
            m_popupWidget->clean_all=false;
            m_pluginWidget->already_start=false;
            m_popupWidget->now_music_name=nullptr;
            not_do_anything=true;
            play_main->stop();
            m_popupWidget->now_playing=0;
            m_pluginWidget->play_files_simple.clear();
            m_pluginWidget->play_files.clear();
            m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
            m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
            m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
            m_popupWidget->show_music->setSpacing(0);
            lyric_text.clear();
            lyric_time.clear();
            m_popupWidget->show_lyric->setText("");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("");
            m_pluginWidget->lyric_main_2->setText("");
        }
        else
        {
            not_do_anything=true;
            int row=m_popupWidget->show_music->currentIndex().row();
            m_pluginWidget->play_files.removeAt(row);
            m_pluginWidget->play_files_simple.removeAt(row);
            if (row==m_popupWidget->now_playing)
            {
                if (m_popupWidget->now_playing==m_pluginWidget->play_files.size())
                {
                    m_popupWidget->now_playing--;
                }
                play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                if (m_pluginWidget->already_start)
                {
                    number_help=-5;
                    play_main->play();
                }
            }
            m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
            m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
            m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
            m_popupWidget->show_music->setSpacing(0);
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
        }
    }
    if (m_popupWidget->del_this)
    {
        m_popupWidget->del_this=false;
        not_do_anything=true;
        if (m_popupWidget->show_music->currentIndex().row()!=-1)
        {
        int row=m_popupWidget->show_music->currentIndex().row();
        QString file_path=m_pluginWidget->play_files[row];
        if (m_pluginWidget->play_files_simple.size()==1)
        {
            out_thing=true;
            m_popupWidget->clean_all=false;
            m_pluginWidget->already_start=false;
            m_popupWidget->now_music_name=nullptr;
            not_do_anything=true;
            play_main->stop();
            m_popupWidget->now_playing=0;
            m_pluginWidget->play_files_simple.clear();
            m_pluginWidget->play_files.clear();
            m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
            m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
            m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
            m_popupWidget->show_music->setSpacing(0);
            lyric_text.clear();
            lyric_time.clear();
            m_popupWidget->show_lyric->setText("");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("");
            m_pluginWidget->lyric_main_2->setText("");
        }
        else
        {
            not_do_anything=true;
            int row=m_popupWidget->show_music->currentIndex().row();
            m_pluginWidget->play_files.removeAt(row);
            m_pluginWidget->play_files_simple.removeAt(row);
            if (row==m_popupWidget->now_playing)
            {
                if (m_popupWidget->now_playing==m_pluginWidget->play_files.size())
                {
                    m_popupWidget->now_playing--;
                }
                play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
                if (m_pluginWidget->already_start)
                {
                    number_help=-5;
                    play_main->play();
                }
            }
            m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
            m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
            m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
            m_popupWidget->show_music->setSpacing(0);
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
        QString files_url=file_path;
        QFile::remove(file_path);
        files_url.chop(3);
        files_url.append("lrc");
        QFile file(files_url);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox MBox;
            MBox.setWindowTitle("是否删除歌词文件");
            MBox.setText("是否删除歌词文件");
            QPushButton *disagreeButton = MBox.addButton("否", QMessageBox::RejectRole);
            QPushButton *agreeButton = MBox.addButton("是", QMessageBox::AcceptRole);
            MBox.exec();
            if (MBox.clickedButton() == agreeButton)
            {
                QFile::remove(files_url);
            }
            if (MBox.clickedButton() == disagreeButton)
            {
            }
        }
        }
    }
    if (m_popupWidget->QS_music_long_move==false)
    {
        if (play_main->duration()!=0)
        {
            m_popupWidget->set_music_time_main->setValue(int(float(play_main->position())/play_main->duration()*100));
        }
        else
        {
            m_popupWidget->set_music_time_main->setValue(0);
        }
    }
    else
    {
        play_main->setPosition(int(float(m_popupWidget->set_music_time_main->value())/100*play_main->duration()));
        if (m_popupWidget->set_music_time_main->value()!=0)
        {
            lyricsID=int(float(m_popupWidget->set_music_time_main->value())/100*lyric_time.size())-1;//what the fuck!
        }
        else
        {
            lyricsID=0;
        }
    }
    if (!m_pluginWidget->on_left_mouse)
    {
        m_popupWidget->QS_music_long_move=false;
    }
    time=int(play_main->position()/1000);
    h=time/3600;
    m=(time-h*3600)/60;
    s=time-h*3600-m*60;
    m_popupWidget->setmusic_time->setText(QString("进度条\n%1:%2:%3").arg(h).arg(m).arg(s));
    if (m_popupWidget->up_this)
    {
        m_popupWidget->up_this=false;
        if (m_popupWidget->show_music->currentIndex().row()!=0&&m_popupWidget->show_music->currentIndex().row()!=-1)
        {
        int row = m_popupWidget->show_music->currentIndex().row();
        if (m_popupWidget->now_playing==row)
        {
            m_popupWidget->now_playing--;
        }
        else if(m_popupWidget->now_playing==row-1)
        {
            m_popupWidget->now_playing++;
        }
        QString help_str=m_pluginWidget->play_files[row-1];
        m_pluginWidget->play_files.replace(row-1,m_pluginWidget->play_files[row]);
        m_pluginWidget->play_files.replace(row,help_str);
        help_str=m_pluginWidget->play_files_simple[row-1];
        m_pluginWidget->play_files_simple.replace(row-1,m_pluginWidget->play_files_simple[row]);
        m_pluginWidget->play_files_simple.replace(row,help_str);
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        QModelIndex index=m_popupWidget->listmodel->index(row-1);
        m_popupWidget->show_music->setCurrentIndex(index);
        m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
    }
    if (m_popupWidget->down_this)
    {
        m_popupWidget->down_this=false;
        if (m_popupWidget->show_music->currentIndex().row()!=m_pluginWidget->play_files.size()-1&&m_popupWidget->show_music->currentIndex().row()!=-1)
        {
        int row = m_popupWidget->show_music->currentIndex().row();
        if (m_popupWidget->now_playing==row)
        {
            m_popupWidget->now_playing++;
        }
        else if(m_popupWidget->now_playing==row+1)
        {
            m_popupWidget->now_playing--;
        }
        QString help_str=m_pluginWidget->play_files[row+1];
        m_pluginWidget->play_files.replace(row+1,m_pluginWidget->play_files[row]);
        m_pluginWidget->play_files.replace(row,help_str);
        help_str=m_pluginWidget->play_files_simple[row+1];
        m_pluginWidget->play_files_simple.replace(row+1,m_pluginWidget->play_files_simple[row]);
        m_pluginWidget->play_files_simple.replace(row,help_str);
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        QModelIndex index=m_popupWidget->listmodel->index(row+1);
        m_popupWidget->show_music->setCurrentIndex(index);
        m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
    }
    if (m_pluginWidget->main_save)
    {
        m_pluginWidget->main_save=false;
        system("mkdir ~/.local/lib/music-island-c++p;touch ~/.local/lib/music-island-c++p/data.txt;touch ~/.local/lib/music-island-c++p/data2.txt");
        string files_name=getenv("HOME")+string("/.local/lib/music-island-c++p/data.txt");
        string files_name2=getenv("HOME")+string("/.local/lib/music-island-c++p/data2.txt");
        fstream f;
        f.open(files_name,ios::out);
        f<<"//data"<<"\n";
        f<<m_popupWidget->set_volume_main->value()<<"\n";
        f<<m_popupWidget->set_music_time_main->value()<<"\n"<<play_main->duration()<<"\n";
        f<<m_popupWidget->set_music_speed_main->value()<<"\n";
        f<<m_popupWidget->now_playing<<"\n";
        f<<m_popupWidget->the_way_of_playing<<"\n";
        f<<m_popupWidget->p<<"\n"<<m_popupWidget->q<<"\n"<<m_popupWidget->n<<"\n"<<m_popupWidget->b<<"\n";
        for(int it=0;it<m_pluginWidget->play_files.size();it++)
        {
            f<<m_pluginWidget->play_files[it].toStdString()<<"\n";
        }
        f.close();
        f.open(files_name2,ios::out);
        f<<"//data2"<<"\n";
        f<<font.toString().toStdString()<<"\n";
        f<<color.name().toStdString()<<"\n";
        f<<m_popupWidget->the_way_of_lyric<<"\n";
        f<<lyric_font.toString().toStdString()<<"\n";
        f<<lyric_color.name().toStdString()<<"\n";
        f<<m_pluginWidget->the_way_of_choose_type<<"\n";
        f<<back_color.red()<<"\n";
        f<<back_color.green()<<"\n";
        f<<back_color.blue()<<"\n";
        f<<back_color.alpha()<<"\n";
        f<<m_pluginWidget->the_way_of_choose_pos<<"\n";
        f<<m_pluginWidget->getting_music_widget->set_volume_main->value()<<endl;
        f<<m_pluginWidget->getting_music_widget->set_music_time_main->value()<<endl;
        f<<m_pluginWidget->getting_music_widget->set_music_speed_main->value()<<endl;
        f.close();
    }
    if (m_pluginWidget->main_load)
    {
        can_load=false;
        system("mkdir ~/.local/lib/music-island-c++p;touch ~/.local/lib/music-island-c++p/data.txt;touch ~/.local/lib/music-island-c++p/data2.txt");
        m_pluginWidget->main_load=false;
        m_pluginWidget->already_start=false;
        m_popupWidget->now_music_name=nullptr;
        not_do_anything=true;
        play_main->stop();
        m_popupWidget->now_playing=0;
        m_pluginWidget->play_files_simple.clear();
        m_pluginWidget->play_files.clear();
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        load_time=-1;
        string files_name=getenv("HOME")+string("/.local/lib/music-island-c++p/data.txt");
        string files_name2=getenv("HOME")+string("/.local/lib/music-island-c++p/data2.txt");
        ifstream load_data;
        load_data.open(files_name,ios::in);
        string s;
        while(getline(load_data,s))
        {
            load_time++;
            if (load_time==1)
            {
                m_popupWidget->set_volume_main->setValue(atoi(s.c_str()));
            }
            if (load_time==2)
            {
                now_time_help=(atoi(s.c_str()));
            }
            if (load_time==3)
            {
                all_time_help=(atoi(s.c_str()));
            }
            if (load_time==4)
            {
                m_popupWidget->set_music_speed_main->setValue(atoi(s.c_str()));
            }
            if (load_time==5)
            {
                m_popupWidget->now_playing=QString::fromStdString(s).toInt();
            }
            if (load_time==6)
            {
                m_popupWidget->the_way_of_playing=(atoi(s.c_str()));
                if (m_popupWidget->the_way_of_playing==1)
                {
                    m_popupWidget->action_all->setIconVisibleInMenu(true);
                    m_popupWidget->action_this->setIconVisibleInMenu(false);
                    m_popupWidget->action_random->setIconVisibleInMenu(false);
                    m_popupWidget->action_math_way->setIconVisibleInMenu(false);
                }
                if (m_popupWidget->the_way_of_playing==2)
                {
                    m_popupWidget->action_all->setIconVisibleInMenu(false);
                    m_popupWidget->action_this->setIconVisibleInMenu(true);
                    m_popupWidget->action_random->setIconVisibleInMenu(false);
                    m_popupWidget->action_math_way->setIconVisibleInMenu(false);
                }
                if (m_popupWidget->the_way_of_playing==3)
                {
                    m_popupWidget->action_all->setIconVisibleInMenu(false);
                    m_popupWidget->action_this->setIconVisibleInMenu(false);
                    m_popupWidget->action_random->setIconVisibleInMenu(true);
                    m_popupWidget->action_math_way->setIconVisibleInMenu(false);
                }
                if (m_popupWidget->the_way_of_playing==4)
                {
                    m_popupWidget->action_all->setIconVisibleInMenu(false);
                    m_popupWidget->action_this->setIconVisibleInMenu(false);
                    m_popupWidget->action_random->setIconVisibleInMenu(false);
                    m_popupWidget->action_math_way->setIconVisibleInMenu(true);
                }
            }
            if (load_time==7)
            {
                m_popupWidget->p=(atoi(s.c_str()));
            }
            if (load_time==8)
            {
                m_popupWidget->q=(atoi(s.c_str()));
            }
            if (load_time==9)
            {
                m_popupWidget->n=(atoi(s.c_str()));
            }
            if (load_time==10)
            {
                m_popupWidget->b=(atoi(s.c_str()));
            }
            if (load_time>10)
            {
                m_pluginWidget->play_files.append(QString::fromStdString(s));
                QUrl url(QString::fromStdString(s));
                m_pluginWidget->play_files_simple.append(url.fileName());
            }
        }
        load_data.close();
        if (load_time>10)
        {
            not_do_anything=true;
            m_pluginWidget->already_start=false;
            m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
            m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
            m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
            m_popupWidget->show_music->setSpacing(0);
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
            m_popupWidget->now_playing = m_popupWidget->show_music->currentIndex().row();
            play_main->setPosition(int(float(now_time_help)/100*all_time_help));
            first_time=true;
            can_load=true;
        }
        load_data.open(files_name2,ios::in);
        load_time=-1;
        while(getline(load_data,s))
        {
            load_time++;
            if (load_time==1)
            {
                font=QString::fromStdString(s);
            }
            if (load_time==2)
            {
                color.setNamedColor(QString::fromStdString(s));
            }
            if (load_time==3)
            {
                m_popupWidget->the_way_of_lyric=QString::fromStdString(s).toInt();
            }
            if (load_time==4)
            {
                lyric_font=QString::fromStdString(s);
            }
            if (load_time==5)
            {
                lyric_color.setNamedColor(QString::fromStdString(s));
            }
            if (load_time==6)
            {
                m_pluginWidget->the_way_of_choose_type=QString::fromStdString(s).toInt();
                if (m_pluginWidget->the_way_of_choose_type==1)
                {
                    m_pluginWidget->button_start_or_stop_movie->setScaledSize(QSize(23, 23));
                    m_pluginWidget->top_panel->setIconVisibleInMenu(true);
                    m_pluginWidget->dock->setIconVisibleInMenu(false);
                }
                if (m_pluginWidget->the_way_of_choose_type==2)
                {
                    m_pluginWidget->button_start_or_stop_movie->setScaledSize(QSize(20, 20));
                    m_pluginWidget->top_panel->setIconVisibleInMenu(false);
                    m_pluginWidget->dock->setIconVisibleInMenu(true);
                }
            }
            if (load_time==7)
            {
                back_color.setRed(QString::fromStdString(s).toInt());
            }
            if (load_time==8)
            {
                back_color.setGreen(QString::fromStdString(s).toInt());
            }
            if (load_time==9)
            {
                back_color.setBlue(QString::fromStdString(s).toInt());
            }
            if (load_time==10)
            {
                back_color.setAlpha(QString::fromStdString(s).toInt());
                m_pluginWidget->lyric_show->only_look->setStyleSheet(QString("background:rgba(%1,%2,%3,%4)").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()).arg(back_color.alpha()));
            }
            if (load_time==11)
            {
                m_pluginWidget->the_way_of_choose_pos=QString::fromStdString(s).toInt();
                if (m_pluginWidget->the_way_of_choose_pos==1)
                {
                    m_pluginWidget->pos_up_down->setIconVisibleInMenu(true);
                    m_pluginWidget->pos_left_right->setIconVisibleInMenu(false);
                    m_pluginWidget->Layout->setDirection(QBoxLayout::LeftToRight);
                    m_pluginWidget->setLayout(m_pluginWidget->Layout);
                }
                if (m_pluginWidget->the_way_of_choose_pos==2)
                {
                    m_pluginWidget->pos_up_down->setIconVisibleInMenu(false);
                    m_pluginWidget->pos_left_right->setIconVisibleInMenu(true);
                    m_pluginWidget->Layout->setDirection(QBoxLayout::Down);
                    m_pluginWidget->setLayout(m_pluginWidget->Layout);
                }
            }
            if (load_time==12)
            {
                m_pluginWidget->getting_music_widget->set_volume_main->setValue(QString::fromStdString(s).toInt());
            }
            if (load_time==13)
            {
                m_pluginWidget->getting_music_widget->set_music_time_main->setValue(QString::fromStdString(s).toInt());
            }
            if (load_time==14)
            {
                m_pluginWidget->getting_music_widget->set_music_speed_main->setValue(QString::fromStdString(s).toInt());
            }
        }
        load_data.close();
        if (load_time>=1)
        {
        m_popupWidget->name->setFont(font);
        m_popupWidget->setvolume->setFont(font);
        m_popupWidget->set_volume_main->setFont(font);
        m_popupWidget->setmusic_time->setFont(font);
        m_popupWidget->set_music_time_main->setFont(font);
        m_popupWidget->setmusic_speed->setFont(font);
        m_popupWidget->set_music_speed_main->setFont(font);
        m_popupWidget->get_music_button->setFont(font);
        m_popupWidget->get_music_text->setFont(font);
        m_popupWidget->getting_music->setFont(font);
        m_popupWidget->show_music->setFont(font);
        m_popupWidget->show_lyric->setFont(font);
        m_popupWidget->show_lyric_next->setFont(font);
        m_tipsWidget->setFont(font);
        m_pluginWidget->show_name->setFont(font);
        }
        if (load_time>=4)
        {
            m_pluginWidget->lyric_main_1->setFont(lyric_font);
            m_pluginWidget->lyric_main_2->setFont(lyric_font);
        }
        if (load_time>=2)
        {
        m_popupWidget->name->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setvolume->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_volume_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setmusic_time->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_music_time_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setmusic_speed->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_music_speed_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->get_music_button->setStyleSheet(QString("QPushButton{background:rgba(0,0,0,10);color:%1}"
                                                               "QPushButton:hover{background:rgba(0,0,0,25);color:%1}").arg(color.name()));
        m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                         "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                         "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
        m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
        m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
        m_pluginWidget->show_name->setStyleSheet(QString("color:%1").arg(color.name()));
        }
        if (load_time>=5)
        {
            m_pluginWidget->lyric_main_1->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
            m_pluginWidget->lyric_main_2->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
        }
        if(load_time>=3)
        {
        if (m_popupWidget->the_way_of_lyric==1)
        {
            m_popupWidget->lyric_show->setIconVisibleInMenu(true);
            m_popupWidget->lyric_hide->setIconVisibleInMenu(false);
            m_popupWidget->lyric_move->setIconVisibleInMenu(false);
            }
        if (m_popupWidget->the_way_of_lyric==2)
        {
            m_popupWidget->lyric_show->setIconVisibleInMenu(false);
            m_popupWidget->lyric_hide->setIconVisibleInMenu(true);
            m_popupWidget->lyric_move->setIconVisibleInMenu(false);
        }
        if (m_popupWidget->the_way_of_lyric==3)
        {
            m_popupWidget->lyric_show->setIconVisibleInMenu(false);
            m_popupWidget->lyric_hide->setIconVisibleInMenu(false);
            m_popupWidget->lyric_move->setIconVisibleInMenu(true);
        }
        }
        if (can_load)
        {
        if(play_main->position()==0&&!m_pluginWidget->already_start)
        {
            lyricsID=0;
        QString files_url=m_pluginWidget->play_files[m_popupWidget->now_playing];
        files_url.chop(3);
        files_url.append("lrc");
        QFile file(files_url);
        lyric_time.clear();
        lyric_text.clear();
        m_popupWidget->show_lyric->setText("");
        m_popupWidget->show_lyric_next->setText("");
        m_pluginWidget->lyric_main_1->setText("");
        m_pluginWidget->lyric_main_2->setText("");
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            ifstream load_data;
            load_data.open(files_url.toStdString(),ios::in);
            string s;
            QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
            while(getline(load_data,s))
            {
                int index = 0;
                QRegularExpressionMatch match;
                match = regularExpression.match(QString::fromStdString(s),index);
                if(match.hasMatch())
                {
                    int totalTime = match.captured(1).toInt() * 60000 + match.captured(2).toInt() * 1000;
                    QString currentText =QString::fromStdString(match.captured(4).toStdString());
                    lyric_text.push_back(currentText);
                    lyric_time.push_back(totalTime);
                }
            }
        }
        else
        {
            m_popupWidget->show_lyric->setText("无歌词");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("无歌词");
            m_pluginWidget->lyric_main_2->setText("");
        }
        }
        }
    }
    if (m_popupWidget->start_get)
    {
        m_popupWidget->start_get=false;
        m_pluginWidget->getting_music_widget->s_music_name=m_popupWidget->get_music_text->text();
        QNetworkRequest request;
        request.setUrl(m_pluginWidget->getting_music_widget->get_music_main(m_pluginWidget->getting_music_widget->s_music_name,m_pluginWidget->getting_music_widget->page));
        m_pluginWidget->getting_music_widget->manager->get(request);
    }
    if (m_pluginWidget->font_setting)
    {
        m_pluginWidget->font_setting=false;
        bool ok;
        QFont now_font=m_pluginWidget->font();
        font=QFontDialog::getFont(&ok,now_font,nullptr);
        if (ok)
        {
            m_popupWidget->name->setFont(font);
            m_popupWidget->setvolume->setFont(font);
            m_popupWidget->set_volume_main->setFont(font);
            m_popupWidget->setmusic_time->setFont(font);
            m_popupWidget->set_music_time_main->setFont(font);
            m_popupWidget->setmusic_speed->setFont(font);
            m_popupWidget->set_music_speed_main->setFont(font);
            m_popupWidget->get_music_button->setFont(font);
            m_popupWidget->get_music_text->setFont(font);
            m_popupWidget->getting_music->setFont(font);
            m_popupWidget->show_music->setFont(font);
            m_popupWidget->show_lyric->setFont(font);
            m_popupWidget->show_lyric_next->setFont(font);
            m_tipsWidget->setFont(font);
            m_pluginWidget->show_name->setFont(font);
        }
    }
    if (m_pluginWidget->color_setting)
    {
        m_pluginWidget->color_setting=false;
        color=QColorDialog::getColor();
        m_popupWidget->name->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setvolume->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_volume_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setmusic_time->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_music_time_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->setmusic_speed->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->set_music_speed_main->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->get_music_button->setStyleSheet(QString("QPushButton{background:rgba(0,0,0,10);color:%1}"
                                                               "QPushButton:hover{background:rgba(0,0,0,25);color:%1}").arg(color.name()));
        m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                         "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                         "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
        m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
        m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
        m_pluginWidget->show_name->setStyleSheet(QString("color:%1").arg(color.name()));
    }
    if (!lyric_time.isEmpty())
    {
        if (play_main->position()>=lyric_time.at(lyricsID))
        {
            if (lyric_time.size()>lyricsID+1)
            {
                lyricsID++;
                m_popupWidget->show_lyric->setText(lyric_text.at(lyricsID-1));
                m_popupWidget->show_lyric_next->setText(lyric_text.at(lyricsID));
                m_pluginWidget->lyric_main_1->setText(lyric_text.at(lyricsID-1));
                m_pluginWidget->lyric_main_2->setText(lyric_text.at(lyricsID));
            }
            else
            {
                m_popupWidget->show_lyric->setText(lyric_text.at(lyricsID));
                m_popupWidget->show_lyric_next->setText("");
                m_pluginWidget->lyric_main_1->setText(lyric_text.at(lyricsID));
                m_pluginWidget->lyric_main_2->setText("");
            }
        }
    }
    else
    {
        if (m_pluginWidget->play_files.isEmpty())
        {
            m_popupWidget->show_lyric->setText("");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("");
            m_pluginWidget->lyric_main_2->setText("");
        }
        else
        {
            m_popupWidget->show_lyric->setText("无歌词");
            m_popupWidget->show_lyric_next->setText("");
            m_pluginWidget->lyric_main_1->setText("无歌词");
            m_pluginWidget->lyric_main_2->setText("");
        }
    }
    if (m_popupWidget->set_lyric_font)
    {
        m_popupWidget->set_lyric_font=false;
        bool ok;
        QFont now_font=m_pluginWidget->font();
        lyric_font=QFontDialog::getFont(&ok,now_font,nullptr);
        if (ok)
        {
            m_pluginWidget->lyric_main_1->setFont(lyric_font);
            m_pluginWidget->lyric_main_2->setFont(lyric_font);
        }
        lyric_color=QColorDialog::getColor();
        m_pluginWidget->lyric_main_1->setStyleSheet(QString("color:%1").arg(lyric_color.name()));
        m_pluginWidget->lyric_main_2->setStyleSheet(QString("color:%1").arg(lyric_color.name()));
    }
    if (m_popupWidget->the_way_of_lyric==1)
    {
        m_pluginWidget->lyric_show->resize(700,90);
        m_pluginWidget->lyric_show->lyric_can_move=true;
    }
    if (m_popupWidget->the_way_of_lyric==2)
    {
        m_pluginWidget->lyric_show->resize(0,0);
    }
    if (m_popupWidget->the_way_of_lyric==3)
    {
        m_pluginWidget->lyric_show->resize(700,90);
        m_pluginWidget->lyric_show->lyric_can_move=false;
    }
    time=int(play_main->position()/1000);
    h=time/3600;
    m=(time-h*3600)/60;
    s=time-h*3600-m*60;
    time_all=int(play_main->duration()/1000);
    time_h=time_all/3600;
    time_m=(time_all-time_h*3600)/60;
    time_s=time_all-time_h*3600-time_m*60;
    m_pluginWidget->show_name->setText("正在播放:"+m_popupWidget->now_music_name+"\n"+QString("%1:%2:%3/%4:%5:%6").arg(h).arg(m).arg(s).arg(time_h).arg(time_m).arg(time_s));
    if (m_popupWidget->set_back_color)
    {
        m_popupWidget->set_back_color=false;
        back_color=QColorDialog::getColor();
        int alpha_color=QInputDialog::getInt(nullptr,"透明度Alpha(0~255)","透明度Alpha(0~255)");
        if (alpha_color>=0&&alpha_color<=255)
        {
            back_color.setAlpha(alpha_color);
        }
        else
        {
            back_color.setAlpha(255);
        }
        m_pluginWidget->lyric_show->only_look->setStyleSheet(QString("background:rgba(%1,%2,%3,%4)").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()).arg(back_color.alpha()));
    }
    m_popupWidget->show_music->setStyleSheet(QString("QListView{background:rgba(0,0,0,0);color:%1}"
                                                     "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:%1}"
                                                     "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255)}").arg(color.name()));
    if ((m_pluginWidget->getting_music_widget->can_get_music_to_list)and(m_pluginWidget->getting_music_widget->doing_getting==false))
    {
        m_pluginWidget->getting_music_widget->can_get_music_to_list=false;
        m_pluginWidget->play_files_simple.append(m_pluginWidget->getting_music_widget->launch_file_name+".mp3");
        m_pluginWidget->play_files.append(m_pluginWidget->getting_music_widget->launch_file_name_all);
        m_popupWidget->listmodel->setStringList(m_pluginWidget->play_files_simple);
        m_popupWidget->show_music->setModel(m_popupWidget->listmodel);
        m_popupWidget->show_music->setEditTriggers(QListView::NoEditTriggers);
        m_popupWidget->show_music->setSpacing(0);
        if (m_popupWidget->show_music->currentIndex().row()==-1 && !m_pluginWidget->already_start)
        {
            QModelIndex index=m_popupWidget->listmodel->index(0);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
            play_main->setMedia(QUrl::fromLocalFile(m_pluginWidget->play_files[m_popupWidget->now_playing]));
        }
        else
        {
            QModelIndex index=m_popupWidget->listmodel->index(m_popupWidget->now_playing);
            m_popupWidget->show_music->setCurrentIndex(index);
            m_popupWidget->now_music_name=m_popupWidget->listmodel->data(index,Qt::DisplayRole).toString();
        }
    }
}
