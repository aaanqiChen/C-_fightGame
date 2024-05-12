#include<QGraphicsScene>
#include<QGraphicsView>
#include<QIcon>
#include <QApplication>
#include"GameSetting.h"
#include"player.h"
#include"score.h"
#include"health.h"
#include<QtMultimedia>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("星空大战");
    QApplication::setWindowIcon(QIcon(":/image2/flight.jpg"));
    //创建player
    Player* player=new Player;

    //创建场景
    QGraphicsScene* scene=new QGraphicsScene;
    scene->addItem(player);
    scene->setSceneRect(0,0,GameSetting::SceneWidth,GameSetting::SceneHeight);
    scene->setBackgroundBrush(QImage(":/images/bg1.jpg"));
    //创建分数文字item
    scene->addItem(&Score::getInstance());
    scene->setStickyFocus(true);//不会在被点击时取消playerfocus状态
    //创建健康值文字
    scene->addItem(&Health::getInstance());

    QGraphicsView view(scene);
    view.setFixedSize(GameSetting::SceneWidth,GameSetting::SceneHeight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    //添加背景音乐
    QMediaPlayer bgMusic;
    QAudioOutput audioOutput;
    bgMusic.setAudioOutput(&audioOutput);
    bgMusic.setSource(QUrl("qrc:/sounds/bgsound.mp3"));
    bgMusic.play();
    return a.exec();
}
