#include "informationpopup.h"
#include<QInputDialog>
#include<QApplication>
#include<QMessageBox>
using namespace std;
InformationPopup::InformationPopup(QWidget *parent)
    :QWidget(parent)
{
    action_all->setIcon(QIcon(":/image/image/this.svg"));
    action_this->setIcon(QIcon(":/image/image/this.svg"));
    action_random->setIcon(QIcon(":/image/image/this.svg"));
    action_math_way->setIcon(QIcon(":/image/image/this.svg"));
    lyric_show->setIcon(QIcon(":/image/image/this.svg"));
    lyric_hide->setIcon(QIcon(":/image/image/this.svg"));
    lyric_move->setIcon(QIcon(":/image/image/this.svg"));
    action_all->setIconVisibleInMenu(true);
    action_this->setIconVisibleInMenu(false);
    action_random->setIconVisibleInMenu(false);
    action_math_way->setIconVisibleInMenu(false);
    lyric_show->setIconVisibleInMenu(false);
    lyric_hide->setIconVisibleInMenu(true);
    lyric_move->setIconVisibleInMenu(false);
    playing_way->addAction(action_all);
    playing_way->addAction(action_this);
    playing_way->addAction(action_random);
    playing_way->addAction(action_math_way);
    lyric_way->addAction(lyric_show);
    lyric_way->addAction(lyric_hide);
    lyric_way->addAction(lyric_move);
    lyric_way->addAction(action_set_lyric_font);
    menu->addMenu(playing_way);
    menu->addAction(action_clean);
    menu->addMenu(lyric_way);
    Qlist_menu->addAction(move_up);
    Qlist_menu->addAction(move_down);
    Qlist_menu->addAction(move_out);
    Qlist_menu->addAction(del_file);
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
    get_music_button->move(0,135);
    get_music_button->resize(75,40);
    get_music_text->move(75,135);
    get_music_text->resize(125,40);
    connect(get_music_button,SIGNAL(clicked()),this,SLOT(get_music_on()));
    show_music->move(200,0);
    show_music->resize(300,180);
    show_music->viewport()->installEventFilter(this);
    resize(size_x_this,180);
    QModelIndex index=listmodel->index(now_playing);
    show_music->setCurrentIndex(index);
    show_lyric->move(0,180);
    show_lyric->resize(225,30);
    show_lyric_next->move(250,180);
    show_lyric_next->resize(225,30);
}
void InformationPopup::qslider_doing(int value)
{
    setvolume->setText("设置音量\n"+QString::number(value)+"%");
}
void InformationPopup::music_value_doing(int value)
{
    QS_music_long_move=true;
}
void InformationPopup::music_value_speed(int value)
{
    setmusic_speed->setText("速度\n"+QString::number(value)+"%");
}
void InformationPopup::get_music_on()
{
    get_music_text->setText(getting_music->getText(nullptr,tr("输入音乐名称"),tr("输入音乐名称"),QLineEdit::Normal,get_music_text->text()));
    start_get=true;
}
void InformationPopup::contextMenuEvent(QContextMenuEvent *event)
{
    if ((event->pos().x()<200)or(event->pos().x()>=200&&event->pos().y()>=180))
    {
    QAction *know_what=menu->exec(mapToGlobal(event->pos()));
    if (know_what==action_clean)
    {
        QMessageBox MBox;
        MBox.setWindowTitle("是否清空");
        MBox.setText("是否清空");
        QPushButton *disagreeButton = MBox.addButton("否", QMessageBox::RejectRole);
        QPushButton *agreeButton = MBox.addButton("是", QMessageBox::AcceptRole);
        MBox.exec();
        if (MBox.clickedButton() == agreeButton)
        {
            clean_all=true;
        }
        if (MBox.clickedButton() == disagreeButton)
        {
        }
    }
    if (know_what==action_all)
    {
        action_all->setIconVisibleInMenu(true);
        action_this->setIconVisibleInMenu(false);
        action_random->setIconVisibleInMenu(false);
        action_math_way->setIconVisibleInMenu(false);
        the_way_of_playing=1;
    }
    if (know_what==action_this)
    {
        action_all->setIconVisibleInMenu(false);
        action_this->setIconVisibleInMenu(true);
        action_random->setIconVisibleInMenu(false);
        action_math_way->setIconVisibleInMenu(false);
        the_way_of_playing=2;
    }
    if (know_what==action_random)
    {
        action_all->setIconVisibleInMenu(false);
        action_this->setIconVisibleInMenu(false);
        action_random->setIconVisibleInMenu(true);
        action_math_way->setIconVisibleInMenu(false);
        the_way_of_playing=3;
    }
    if (know_what==action_math_way)
    {
        action_all->setIconVisibleInMenu(false);
        action_this->setIconVisibleInMenu(false);
        action_random->setIconVisibleInMenu(false);
        action_math_way->setIconVisibleInMenu(true);
        p=QInputDialog::getInt(nullptr,"获取","获取p,y=(p/q)x^n+b (x为当前,y为目标)");
        q=QInputDialog::getInt(nullptr,"获取","获取q,y=(p/q)x^n+b (x为当前,y为目标)");
        n=QInputDialog::getInt(nullptr,"获取","获取n,y=(p/q)x^n+b (x为当前,y为目标)");
        b=QInputDialog::getInt(nullptr,"获取","获取b,y=(p/q)x^n+b (x为当前,y为目标)");
        the_way_of_playing=4;
    }
    if (know_what==lyric_show)
    {
        lyric_show->setIconVisibleInMenu(true);
        lyric_hide->setIconVisibleInMenu(false);
        lyric_move->setIconVisibleInMenu(false);
        the_way_of_lyric=1;
    }
    if (know_what==lyric_hide)
    {
        lyric_show->setIconVisibleInMenu(false);
        lyric_hide->setIconVisibleInMenu(true);
        lyric_move->setIconVisibleInMenu(false);
        the_way_of_lyric=2;
    }
    if (know_what==lyric_move)
    {
        lyric_show->setIconVisibleInMenu(false);
        lyric_hide->setIconVisibleInMenu(false);
        lyric_move->setIconVisibleInMenu(true);
        the_way_of_lyric=3;
    }
    if (know_what==action_set_lyric_font)
    {
        set_lyric_font=true;
    }
    }
    else
    {
        QAction *know_what=Qlist_menu->exec(mapToGlobal(event->pos()));
        if (know_what==move_up)
        {
            up_this=true;
        }
        if (know_what==move_down)
        {
            down_this=true;
        }
        if (know_what==move_out)
        {
            QMessageBox MBox;
            MBox.setWindowTitle("是否移除");
            MBox.setText("是否移除");
            QPushButton *disagreeButton = MBox.addButton("否", QMessageBox::RejectRole);
            QPushButton *agreeButton = MBox.addButton("是", QMessageBox::AcceptRole);
            MBox.exec();
            if (MBox.clickedButton() == agreeButton)
            {
                out_this=true;
            }
            if (MBox.clickedButton() == disagreeButton)
            {
            }
        }
        if (know_what==del_file)
        {
            QMessageBox MBox;
            MBox.setWindowTitle("是否删除");
            MBox.setText("是否删除");
            QPushButton *disagreeButton = MBox.addButton("否", QMessageBox::RejectRole);
            QPushButton *agreeButton = MBox.addButton("是", QMessageBox::AcceptRole);
            MBox.exec();
            if (MBox.clickedButton() == agreeButton)
            {
                del_this=true;
            }
            if (MBox.clickedButton() == disagreeButton)
            {
            }
        }
    }
}
bool InformationPopup::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == show_music->viewport())
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            QVariant text1 = show_music->selectionModel()->selectedIndexes()[0].data();
            now_music_name = text1.toString();
            now_playing = show_music->currentIndex().row();
            change=true;
        }
    }
}
