#include "informationgetmusic.h"
#include<fstream>
InformationGetmusic::InformationGetmusic(QWidget *parent)
    :QWidget(parent)
{
    connect(manager,SIGNAL(finished(QNetworkReply *)),this,SLOT(getting_music(QNetworkReply *)));
    connect(manager_lyric,SIGNAL(finished(QNetworkReply *)),this,SLOT(getting_lyric(QNetworkReply *)));
    setWindowFlag(Qt::WindowCloseButtonHint);
    setWindowTitle("music-island试听");
    resize(500,270);
    name->move(50,0);
    setvolume->move(0,15);
    set_volume_main->move(50,15);
    set_volume_main->resize(150,40);
    set_volume_main->setMinimum(0);
    set_volume_main->setMaximum(100);
    set_volume_main->setSingleStep(10);
    set_volume_main->setValue(100);
    set_volume_main->setTickPosition(QSlider::TicksBelow);
    set_volume_main->setTickInterval(10);
    connect(set_volume_main, SIGNAL(valueChanged(int)), this, SLOT(qslider_doing(int)));
    setmusic_time->move(0,55);
    set_music_time_main->move(50,55);
    set_music_time_main->resize(150,40);
    set_music_time_main->setMinimum(0);
    set_music_time_main->setMaximum(100);
    set_music_time_main->setSingleStep(10);
    set_music_time_main->setValue(now_music_long);
    set_music_time_main->setTickPosition(QSlider::TicksBelow);
    set_music_time_main->setTickInterval(10);
    connect(set_music_time_main, SIGNAL(valueChanged(int)), this, SLOT(music_value_doing(int)));
    setmusic_speed->move(0,95);
    set_music_speed_main->move(50,95);
    set_music_speed_main->resize(150,40);
    set_music_speed_main->setMinimum(10);
    set_music_speed_main->setMaximum(300);
    set_music_speed_main->setSingleStep(10);
    set_music_speed_main->setValue(100);
    set_music_speed_main->setTickPosition(QSlider::TicksBelow);
    set_music_speed_main->setTickInterval(10);
    connect(set_music_speed_main, SIGNAL(valueChanged(int)), this, SLOT(music_value_speed(int)));
    show_reply_music->move(200,0);
    show_reply_music->resize(300,230);
    try_to_listen_button_play->move(0,140);
    try_to_listen_button_play->resize(75,40);
    try_to_listen_button_pause->move(80,140);
    try_to_listen_button_pause->resize(75,40);
    connect(try_to_listen_button_play,SIGNAL(clicked()),this,SLOT(try_to_listen_button_play_click()));
    connect(try_to_listen_button_pause,SIGNAL(clicked()),this,SLOT(try_to_listen_button_pause_click()));
    get_it_button->move(0,185);
    do_not_get_button->move(80,185);
    get_it_button->resize(75,40);
    do_not_get_button->resize(75,40);
    connect(get_it_button,SIGNAL(clicked()),this,SLOT(get_it_button_click()));
    connect(do_not_get_button,SIGNAL(clicked()),this,SLOT(do_not_get_button_click()));
    up_page->move(160,140);
    up_page->resize(40,40);
    down_page->move(160,185);
    down_page->resize(40,40);
    connect(up_page,SIGNAL(clicked()),this,SLOT(up_page_button_click()));
    connect(down_page,SIGNAL(clicked()),this,SLOT(down_page_button_click()));
    only_music->move(0,230);
    only_music->resize(95,40);
    only_lyric->move(100,230);
    only_lyric->resize(95,40);
    connect(only_music,SIGNAL(clicked()),this,SLOT(only_music_click()));
    connect(only_lyric,SIGNAL(clicked()),this,SLOT(only_lyric_click()));
    button_timer->setInterval(30);
    connect(button_timer,SIGNAL(timeout()),this,SLOT(timer_of_button()));
    button_timer->start();
}
void InformationGetmusic::qslider_doing(int value)
{
    setvolume->setText("设置音量\n"+QString::number(value)+"%");
    try_to_listen->setVolume(value);
}
void InformationGetmusic::music_value_doing(int value)
{
    if (HS_time_moving==false)
    {
        try_to_listen->setPosition(try_to_listen->duration()*value/100);
    }
}
void InformationGetmusic::music_value_speed(int value)
{
    setmusic_speed->setText("速度\n"+QString::number(value)+"%");
    try_to_listen->setPlaybackRate(qreal(float(value)/100));
}
QString InformationGetmusic::get_music_main(QString s_music_name,int page)
{
    if ((s_music_name!=nullptr)and(page>=0))
    {
        QString url="http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s={"+s_music_name+"}&type=1&offset="+QString::number(page)+"&total=true&limit=10";
        return url;
    }
    else
    {
        return nullptr;
    }
}
void InformationGetmusic::getting_music(QNetworkReply *reply)
{
    doing_getting=true;
    show();
    QString get_artists;
    QByteArray get_reply=reply->readAll();
    QJsonParseError error;
    QJsonDocument json_recv = QJsonDocument::fromJson(get_reply,&error);
    reply_music_list.clear();
    name_to_filesname.clear();
    reply_music_to_url.clear();
    get_music_id.clear();
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
                    if (!object1.contains("fee")||object1["fee"].toInt()!=1)
                    {
                    get_music_id.append(static_cast<long>(object1["id"].toDouble()));//int不够用
                    QStringList artistsKeys = object1.keys();
                    if(artistsKeys.contains("artists"))
                    {
                        QJsonArray artistsArray = object1["artists"].toArray();
                        get_artists.clear();
                        for(auto j : artistsArray)
                        {
                            QJsonObject object2 = j.toObject();
                            if(get_artists==nullptr)
                            {
                                get_artists=object2["name"].toString();
                            }
                            else
                            {
                                get_artists.append("&");
                                get_artists.append(object2["name"].toString());
                            }
                        }
                        QString music_name=QString(object1["name"].toString()+"--"+get_artists+"--"+QString::number(static_cast<long>(object1["id"].toDouble()))).replace("'","").replace('"',"").replace("/","");
                        QString files_name=QString(object1["name"].toString()+"--"+get_artists).replace("'","").replace('"',"").replace("/","");
                        QString music_id=QString::number(static_cast<long>(object1["id"].toDouble()));
                        reply_music_list.append(music_name);
                        name_to_filesname.insert(music_name,files_name);
                        reply_music_to_url.insert(music_name,QUrl("http://music.163.com/song/media/outer/url?id="+music_id));
                    }
                    else
                    {
                        QString music_name=QString(object1["name"].toString()+"--"+QString::number(static_cast<long>(object1["id"].toDouble()))).replace("'","").replace('"',"").replace("/","");
                        QString files_name=QString(object1["name"].toString()+"--").replace("'","").replace('"',"").replace("/","");
                        QString music_id=QString::number(static_cast<long>(object1["id"].toDouble()));
                        reply_music_list.append(music_name);
                        name_to_filesname.insert(music_name,files_name);
                        reply_music_to_url.insert(music_name,QUrl("http://music.163.com/song/media/outer/url?id="+music_id));
                    }
                    }
                }
            }
        }
    }
    if (get_music_id.isEmpty())
    {
        reply_music_list.append(QString::number(page));
        listmodel->setStringList(reply_music_list);
        show_reply_music->setModel(listmodel);
        show_reply_music->setEditTriggers(QListView::NoEditTriggers);
        show_reply_music->setSpacing(0);
    }
    else
    {
    listmodel->setStringList(reply_music_list);
    show_reply_music->setModel(listmodel);
    show_reply_music->setEditTriggers(QListView::NoEditTriggers);
    show_reply_music->setSpacing(0);
    QModelIndex index=listmodel->index(0);
    show_reply_music->setCurrentIndex(index);
    if (try_to_listen->position()==0||try_to_listen->position()==try_to_listen->duration())
    {
        try_to_listen->setMedia(QUrl(reply_music_list[0]));
    }
    }
}
void InformationGetmusic::getting_lyric(QNetworkReply *reply)
{
    if (show_reply_music->currentIndex().row()!=-1)
    {
        QVariant text1 = show_reply_music->selectionModel()->selectedIndexes()[0].data();
        QString files_name_all=getenv("HOME")+QString("/.local/lib/music-island-c++p/music_downloads/"+name_to_filesname[text1.toString()]+".mp3");
        if (get_music_way!=2)
        {
    system("mkdir ~/.local/lib/music-island-c++p/music_downloads");
    QString run1="wget "+reply_music_to_url[text1.toString()].toString()+" -O '"+files_name_all+"'";
    string run2=run1.toStdString();
    const char* run3=run2.c_str();
    system(run3);
        }
    QByteArray get_reply_lyric=reply->readAll();
    string lyric_main;
    QJsonParseError error;
    QJsonDocument json_recv = QJsonDocument::fromJson(get_reply_lyric,&error);
    if(error.error != QJsonParseError::NoError)
    {
        QMessageBox::information(nullptr,"无答复",QString::number(get_music_id[show_reply_music->currentIndex().row()]));
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
        if (get_music_way==0)
        {
        QString run1="touch '~/.local/lib/music-island-c++p/music_downloads/"+name_to_filesname[text1.toString()]+".lrc'";
        string run2=run1.toStdString();
        const char* run3=run2.c_str();
        system(run3);
        string open_files_name=getenv("HOME")+string("/.local/lib/music-island-c++p/music_downloads/")+name_to_filesname[text1.toString()].toStdString()+".lrc";
        fstream f;
        f.open(open_files_name,ios::out);
        f<<lyric_main;
        f.close();
        }
        if (get_music_way==2)
        {
            if (find_lyric_use_name==nullptr)
            {
                QMessageBox::information(nullptr,"find_lyric_use_name==nullptr","true");
            }
            else
            {
                int index;
                index=find_lyric_use_name.lastIndexOf(".");
                find_lyric_use_name.truncate(index);
                find_lyric_use_name.append(".lrc");
                QString run1="touch '"+find_lyric_use_name+"'";
                string run2=run1.toStdString();
                const char* run3=run2.c_str();
                system(run3);
                fstream f;
                f.open(find_lyric_use_name.toStdString(),ios::out);
                f<<lyric_main;
                f.close();
            }
        }
    }
    launch_file_name=name_to_filesname[text1.toString()];
    launch_file_name_all=files_name_all;
    if (get_music_way!=2)
    {
    can_get_music_to_list=true;
    }
    else
    {
        can_get_music_to_list=false;
    }
    }
    QMessageBox::information(nullptr,"搞定","pass!");
    hide();
    get_music_way=0;
    find_lyric_use_name=nullptr;
    doing_getting=false;
}
void InformationGetmusic::try_to_listen_button_play_click()
{
    if (show_reply_music->currentIndex().row()!=-1)
    {
        QVariant text1 = show_reply_music->selectionModel()->selectedIndexes()[0].data();
        if (try_to_listen->media()!=reply_music_to_url[text1.toString()])
        {
        try_to_listen->setMedia(reply_music_to_url[text1.toString()]);
        }
        number_help=-5;
        try_to_listen->play();
    }
}
void InformationGetmusic::try_to_listen_button_pause_click()
{
    number_help=95;
}
void InformationGetmusic::timer_of_button()
{
    HS_time_moving=true;
        if (try_to_listen->duration()!=0)
        {
            set_music_time_main->setValue(int(float(try_to_listen->position())/try_to_listen->duration()*100));
        }
        else
        {
            set_music_time_main->setValue(0);
        }
    HS_time_moving=false;
    time=int(try_to_listen->position()/1000);
    h=time/3600;
    m=(time-h*3600)/60;
    s=time-h*3600-m*60;
    setmusic_time->setText(QString("进度条\n%1:%2:%3").arg(h).arg(m).arg(s));
    if ((abs(number_help))==100)
    {
        try_to_listen->setVolume(set_volume_main->value());
    }
    else
    {
        try_to_listen->setVolume(abs(number_help));
    }
    if ((abs(number_help))<100)
    {
        number_help-=5;
    }
    if (number_help==0)
    {
        try_to_listen->pause();
        number_help=-100;
    }
    if (isHidden())
    {
        try_to_listen->stop();
        page=0;
    }
}
void InformationGetmusic::get_it_button_click()
{
    if (show_reply_music->currentIndex().row()!=-1)
    {
        get_music_way=0;
        find_lyric_use_name=nullptr;
    QString url_lyric="http://music.163.com/api/song/lyric?id="+QString::number(get_music_id[show_reply_music->currentIndex().row()])+"&lv=1&kv=1&tv=-1";
    QNetworkRequest request;
    request.setUrl(url_lyric);
    manager_lyric->get(request);
    }
}
void InformationGetmusic::do_not_get_button_click()
{
    doing_getting=false;
    close();
}
void InformationGetmusic::up_page_button_click()
{
    if (page>0)
    {
        page--;
        QNetworkRequest request;
        request.setUrl(get_music_main(s_music_name,page));
        manager->get(request);
    }
}
void InformationGetmusic::down_page_button_click()
{
    page++;
    QNetworkRequest request;
    request.setUrl(get_music_main(s_music_name,page));
    manager->get(request);
}
void InformationGetmusic::only_music_click()
{
    if (show_reply_music->currentIndex().row()!=-1)
    {
        get_music_way=1;
        find_lyric_use_name=nullptr;
    QString url_lyric="http://music.163.com/api/song/lyric?id="+QString::number(get_music_id[show_reply_music->currentIndex().row()])+"&lv=1&kv=1&tv=-1";
    QNetworkRequest request;
    request.setUrl(url_lyric);
    manager_lyric->get(request);
    }
}
void InformationGetmusic::only_lyric_click()
{
    if (show_reply_music->currentIndex().row()!=-1)
    {
        get_music_way=2;
    QString url_lyric="http://music.163.com/api/song/lyric?id="+QString::number(get_music_id[show_reply_music->currentIndex().row()])+"&lv=1&kv=1&tv=-1";
    QNetworkRequest request;
    request.setUrl(url_lyric);
    manager_lyric->get(request);
    }
}
