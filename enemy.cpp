#include "enemy.h"
#include<QPixmap>
#include"GameSetting.h"
#include<QRandomGenerator>
#include<QGraphicsScene>
#include"player.h"
#include"bullet.h"
#include"score.h"
#include"health.h"

Enemy::Enemy(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/image2/enemy.jpg"));
    setScale(GameSetting::EnemyScale);
    int max=GameSetting::SceneWidth-boundingRect().width()*GameSetting::EnemyScale;
    int randomNumber=QRandomGenerator::global()->bounded(1,max);
    setPos(randomNumber,0);
    startTimer(GameSetting::EnemyTimer);

}


void Enemy::timerEvent(QTimerEvent *)
{
    QList<QGraphicsItem*>itemList=collidingItems();
    for(auto item:itemList){
        if(typeid(*item)==typeid(Player)){
            //健康值需要decrease
            Health::getInstance().decrease();
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
    setPos(x(),y()+GameSetting::EnemySpeed);
    if(y()>GameSetting::SceneHeight){
        scene()->removeItem(this);
        delete this;
        return;
    }
}
