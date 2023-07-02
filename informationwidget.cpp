#include "informationwidget.h"
#include "informationpopup.h"
#include "keyscan.h"
#include<stdlib.h>
#include<iostream>
#include<QContextMenuEvent>
#include<QMimeData>
#include<QMimeDatabase>
#include<QFileDialog>
#include<iostream>
#include<fstream>
using namespace std;
void InformationWidget::timer_of_button()
{
    button_back_movie->start();
    button_next_movie->start();
    button_start_or_stop_movie->start();
    if (((mouse->pos().x()-button_back->mapToGlobal(QPoint(0,0)).x())<15)and((mouse->pos().x()-button_back->mapToGlobal(QPoint(0,0)).x())>0)and((mouse->pos().y()-button_back->mapToGlobal(QPoint(0,0)).y())<20)and((mouse->pos().y()-button_back->mapToGlobal(QPoint(0,0)).y())>0))
    {
        button_back_movie->jumpToFrame(1);
        can_popup=false;
        if (on_left_mouse==true)
        {
            back_music=true;
        }
    }
    else
    {
        button_back_movie->jumpToFrame(0);
        can_popup=true;
    }
    if (((mouse->pos().x()-button_next->mapToGlobal(QPoint(0,0)).x())<15)and(mouse->pos().x()-button_next->mapToGlobal(QPoint(0,0)).x()>0)and((mouse->pos().y()-button_next->mapToGlobal(QPoint(0,0)).y())<20)and((mouse->pos().y()-button_next->mapToGlobal(QPoint(0,0)).y())>0))
    {
        button_next_movie->jumpToFrame(1);
        can_popup=false;
        if (on_left_mouse==true)
        {
            next_music=true;
        }
    }
    else
    {
        button_next_movie->jumpToFrame(0);
    }
    if (((mouse->pos().x()-button_start_or_stop->mapToGlobal(QPoint(0,0)).x())<23)and(mouse->pos().x()-button_start_or_stop->mapToGlobal(QPoint(0,0)).x()>0)and((mouse->pos().y()-button_start_or_stop->mapToGlobal(QPoint(0,0)).y())<23)and((mouse->pos().y()-button_start_or_stop->mapToGlobal(QPoint(0,0)).y())<23))
    {
        if (already_start==false)
        {
            button_start_or_stop_movie->jumpToFrame(1);
        }
        else
        {
            button_start_or_stop_movie->jumpToFrame(3);
        }
        if (on_left_mouse==true)
        {
            if (!play_files.empty())
            {
            already_start=not already_start;
            already_start_this=true;
            }
        }
        can_popup=false;
    }
    else
    {
        if (already_start==false)
        {
            button_start_or_stop_movie->jumpToFrame(0);
        }
        else
        {
            button_start_or_stop_movie->jumpToFrame(2);
        }
    }
    button_back_movie->stop();
    button_next_movie->stop();
    button_start_or_stop_movie->stop();
    button_back->show();
    button_next->show();
    button_start_or_stop->show();
    if (on_left_mouse==true)
    {
        on_left_mouse=false;
    }
}
void InformationWidget::set_movie()
{}
InformationWidget::InformationWidget(QWidget *parent)
    :QWidget(parent)
{
    /*ifstream load_data;
    load_data.open(":/image/mainjson.txt",ios::in);
    string s;
    while(load_data>>s)
    {
        load_data>>now_music_long>>the_way_of_playing>>volume_value>>now_playing>>s;
    }
    load_data.close();*/
    setAcceptDrops(true);
    menu->addAction(open_music);
    menu->addAction(save_main);
    menu->addAction(load_main);
    button_back_movie->setFileName(":/image/image/back.gif");
    button_next_movie->setFileName(":/image/image/next.gif");
    button_start_or_stop_movie->setFileName(":/image/image/start_stop.gif");
    button_back_movie->setCacheMode(QMovie::CacheAll);
    button_next_movie->setCacheMode(QMovie::CacheAll);
    button_start_or_stop_movie->setCacheMode(QMovie::CacheAll);
    button_back->setMovie(button_back_movie);
    button_next->setMovie(button_next_movie);
    button_start_or_stop->setMovie(button_start_or_stop_movie);
    button_back_movie->setScaledSize(QSize(15, 15));
    button_next_movie->setScaledSize(QSize(15, 15));
    button_start_or_stop_movie->setScaledSize(QSize(23, 23));
    button_back_movie->start();
    button_back_movie->stop();
    button_next_movie->start();
    button_next_movie->stop();
    button_start_or_stop_movie->start();
    button_start_or_stop_movie->stop();
    button_back_movie->jumpToFrame(0);
    button_next_movie->jumpToFrame(0);
    button_start_or_stop_movie->jumpToFrame(0);
    keyScan * btnCheck = new keyScan(this);
    connect(btnCheck,&keyScan::sig_buttonPressed,this,[=](unsigned char c){
        if (c==1)
        {
            on_left_mouse=true;
        }
    });
    btnCheck->start();
    button_timer->setInterval(30);
    connect(button_timer,SIGNAL(timeout()),this,SLOT(timer_of_button()));
    button_timer->start();
    the_setting_call->setPixmap(QPixmap::fromImage(*setting_call_image).scaled(23,23));
    Layout->addWidget(button_back);
    Layout->addWidget(button_start_or_stop);
    Layout->addWidget(button_next);
    Layout->addWidget(the_setting_call);
    Layout->setMargin(0);
    Layout->setSpacing(0);
    setLayout(Layout);
    button_back->show();
    button_next->show();
    button_start_or_stop->show();
    show();
}
void InformationWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QAction *know_what=menu->exec(mapToGlobal(event->pos()));
    if (know_what==open_music)
    {
        QList<QUrl> urls=QFileDialog::getOpenFileUrls(nullptr,"音乐文件");
        QMimeDatabase db;
        for(int i=0;i<urls.size();i++)
        {
            QMimeType mime =db.mimeTypeForFile(urls.at(i).toLocalFile());
            if (mime.name().startsWith("audio/"))
            {
                play_files.append(urls.at(i).toLocalFile());
                play_files_simple.append(urls.at(i).fileName());
                can_clone=true;
            }
        }
    }
    if (know_what==save_main)
    {
        main_save=true;
    }
    if (know_what==load_main)
    {
        main_load=true;
    }
}
void InformationWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->accept();
    }
}
void InformationWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        QList<QUrl> urls=event->mimeData()->urls();
        QMimeDatabase db;
        for(int i=0;i<urls.size();i++)
        {
            QMimeType mime =db.mimeTypeForFile(urls.at(i).toLocalFile());
            if (mime.name().startsWith("audio/"))
            {
                play_files.append(urls.at(i).toLocalFile());
                play_files_simple.append(urls.at(i).fileName());
                can_clone=true;
            }
        }
    }
}
