#include "stone.h"
#include<QPixmap>
#include"GameSetting.h"
#include<QRandomGenerator>
#include<QGraphicsScene>
#include"player.h"
#include"bullet.h"
#include"score.h"
#include"health.h"

Stone::Stone(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/image2/stone.jpg"));
    setScale(GameSetting::StoneScale);
    int max=GameSetting::SceneWidth-boundingRect().width()*GameSetting::StoneScale;
    int randomNumber=QRandomGenerator::global()->bounded(1,max);
    setPos(randomNumber,0);
    startTimer(GameSetting::StoneTimer);
}

void Stone::timerEvent(QTimerEvent *)
{
    QList<QGraphicsItem*>itemList=collidingItems();
    for(auto item:itemList){
        if(typeid(*item)==typeid(Player)){
            //健康值需要decrease
            Health::getInstance().decrease2();
            scene()->removeItem(this);
            delete this;
            return;
        }
        if(typeid(*item)==typeid(Bullet)){
            //需要减分
            Score::getInstance().decrease();
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }
    setPos(x(),y()+GameSetting::StoneSpeed);
    if(y()>GameSetting::SceneHeight){
        scene()->removeItem(this);
        delete this;
        return;
    }
}


