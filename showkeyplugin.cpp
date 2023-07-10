#include "showkeyplugin.h"
#include<QListView>
#include<QMessageBox>
#include<unistd.h>
#include<fstream>
#include<QFontDialog>
#include<QColorDialog>
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
    connect(manager,SIGNAL(finished(QNetworkReply *)),this,SLOT(getting_music(QNetworkReply *)));
    connect(manager_lyric,SIGNAL(finished(QNetworkReply *)),this,SLOT(getting_lyric(QNetworkReply *)));
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
    m_popupWidget->get_music_button->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->show_music->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
    m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
    m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
    }
    if (load_time>=5)
    {
    m_pluginWidget->lyric_show->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
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
    if (wait_time>0)
    {
        wait_time--;
        if (wait_time==0)
        {
            if ((try_play->duration()==0)and(!first_try_time))
            {
                QMessageBox::information(nullptr,"非audio文件","非audio文件");
                QFile::remove(files_name_all);
            }
            if((try_play->duration()!=0)and(!first_try_time))
            {
                try_play->stop();
                m_pluginWidget->play_files.append(files_name_all);
                m_pluginWidget->play_files_simple.append(files_name);
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
            if(first_try_time)
            {
                first_try_time=false;
                try_play->setVolume(0);
                try_play->setMedia(QUrl::fromLocalFile(files_name_all));
                try_play->play();
                try_play->setPosition(try_play->duration());
                try_play->stop();
                try_play->play();
                wait_time=3;
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
        m_popupWidget->get_music_button->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
        m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
        }
        if (load_time>=5)
        {
        m_pluginWidget->lyric_show->setStyleSheet(QString("font-size:20px;color:%1").arg(lyric_color.name()));
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
    if (m_popupWidget->start_get)
    {
        m_popupWidget->start_get=false;
        QString name=m_popupWidget->get_music_text->text();
        if (name!=nullptr)
        {
            QString url="http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s={"+name+"}&type=1&offset=0&total=true&limit=9";
            QNetworkRequest request;
            request.setUrl(url);
            manager->get(request);
        }
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
        m_popupWidget->get_music_button->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->get_music_text->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->getting_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_music->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric->setStyleSheet(QString("color:%1").arg(color.name()));
        m_popupWidget->show_lyric_next->setStyleSheet(QString("color:%1").arg(color.name()));
        m_tipsWidget->setStyleSheet(QString("color:%1").arg(color.name()));
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
        m_pluginWidget->lyric_show->setStyleSheet(QString("color:%1").arg(lyric_color.name()));
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
}
void ShowKeyPlugin::getting_music(QNetworkReply *reply)
{
    get_music_id.clear();
    get_music_name.clear();
    get_music_name_and_id.clear();
    get_reply=reply->readAll();
    QJsonParseError error;
    QJsonDocument json_recv = QJsonDocument::fromJson(get_reply,&error);
    if(error.error != QJsonParseError::NoError)
    {
        QMessageBox::information(nullptr,"非法字符","非法字符");
    }
    else
    {
        QJsonObject totalObject = json_recv.object();
        QStringList keys = totalObject.keys();
        if(keys.contains("result"))
        {
            QJsonObject resultObject = totalObject["result"].toObject();
            QStringList resultKeys = resultObject.keys();
            if(resultKeys.contains("songs"))
            {
                QJsonArray array = resultObject["songs"].toArray();
                for(auto i : array)
                {
                    QJsonObject object1 = i.toObject();
                    get_music_id.append(object1["id"].toInt());
                    QStringList artistsKeys = object1.keys();
                    if(artistsKeys.contains("artists"))
                    {
                        QJsonArray artistsArray = object1["artists"].toArray();
                        for(auto j : artistsArray)
                        {
                            QJsonObject object2 = j.toObject();
                            get_music_name.append(object1["name"].toString()+"--"+object2["name"].toString());
                            get_music_name_and_id.append(object1["name"].toString()+"--"+object2["name"].toString()+"--"+QString::number(object1["id"].toInt()));
                        }
                    }
                    else
                    {
                        get_music_name.append(object1["name"].toString());
                        get_music_name_and_id.append(object1["name"].toString()+"--"+QString::number(object1["id"].toInt()));
                    }
                }
                bool bool_ok=false;
                QString get_choose_name=QInputDialog::getItem(nullptr,"获取","获取",get_music_name_and_id,0,false,&bool_ok);
                if ((bool_ok)and(get_choose_name!=nullptr))
                {
                    system("mkdir ~/.local/lib/music-island-c++p/music_downloads");
                    QString get_url_name="http://music.163.com/song/media/outer/url?id="+QString::number(get_music_id[get_music_name_and_id.indexOf(get_choose_name)]);
                    files_name=get_music_name[get_music_name_and_id.indexOf(get_choose_name)].replace("'","").replace('"',"").replace("/","");
                    files_name_all=getenv("HOME")+QString("/.local/lib/music-island-c++p/music_downloads/"+files_name+".mp3");
                    QString run1="wget "+get_url_name+" -O '"+files_name_all+"'";
                    string run2=run1.toStdString();
                    const char* run3=run2.c_str();
                    QString url_lyric="http://music.163.com/api/song/lyric?id="+QString::number(get_music_id[get_music_name_and_id.indexOf(get_choose_name)])+"&lv=1&kv=1&tv=-1";
                    QNetworkRequest request;
                    request.setUrl(url_lyric);
                    manager_lyric->get(request);
                    system(run3);
                    try_play->setVolume(0);
                    try_play->setMedia(QUrl::fromLocalFile(files_name_all));
                    try_play->play();
                    try_play->setPosition(try_play->duration());
                    try_play->stop();
                    try_play->play();
                    wait_time=3;
                }
            }
            else
            {
                QMessageBox::information(nullptr,"无结果","无结果");
            }
        }
        else
        {
            QMessageBox::information(nullptr,"无结果","无结果");
        }
    }
}
void ShowKeyPlugin::getting_lyric(QNetworkReply *reply)
{
    get_reply_lyric=reply->readAll();
    QJsonParseError error;
    QJsonDocument json_recv = QJsonDocument::fromJson(get_reply_lyric,&error);
    if(error.error != QJsonParseError::NoError)
    {
        QMessageBox::information(nullptr,"无答复","无答复");
    }
    else
    {
        QJsonObject totalObject=json_recv.object();
        QStringList keys=totalObject.keys();
        if(keys.contains("lrc"))
        {
            QJsonObject resultObject=totalObject["lrc"].toObject();
            QStringList resultkeys=resultObject.keys();
            if(resultkeys.contains("lyric"))
            {
                lyric_main=resultObject["lyric"].toString().toStdString();
            }
        }
        QString run1="touch '~/.local/lib/music-island-c++p/music_downloads/"+files_name+".lrc'";
        string run2=run1.toStdString();
        const char* run3=run2.c_str();
        system(run3);
        string open_files_name=getenv("HOME")+string("/.local/lib/music-island-c++p/music_downloads/")+files_name.toStdString()+".lrc";
        fstream f;
        f.open(open_files_name,ios::out);
        f<<lyric_main;
        f.close();
    }
}
