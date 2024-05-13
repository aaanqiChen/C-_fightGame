#include "star.h"
#include<QPixmap>
#include"GameSetting.h"
#include<QRandomGenerator>
#include<QGraphicsScene>
#include"player.h"
#include"bullet.h"
#include"score.h"
#include"health.h"

Star::Star(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/image2/star.jpg"));
    setScale(GameSetting::StarScale);
    int max=GameSetting::SceneWidth-boundingRect().width()*GameSetting::StarScale;
    int randomNumber=QRandomGenerator::global()->bounded(1,max);
    setPos(randomNumber,0);
    startTimer(GameSetting::StarTimer);

}


void Star::timerEvent(QTimerEvent *)
{
    QList<QGraphicsItem*>itemList=collidingItems();
    for(auto item:itemList){
        if(typeid(*item)==typeid(Player)){
            //健康值需要decrease
            Health::getInstance().decrease1();
            scene()->removeItem(this);
            delete this;
            return;
        }
        if(typeid(*item)==typeid(Bullet)){
            //需要加分
            Score::getInstance().increase();
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }
    setPos(x(),y()+GameSetting::StarSpeed);
    if(y()>GameSetting::SceneHeight){
        scene()->removeItem(this);
        delete this;
        return;
    }
}
