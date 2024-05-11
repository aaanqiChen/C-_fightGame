#include "bullet.h"
#include<QPixmap>
#include"GameSetting.h"
#include<QGraphicsScene>

Bullet::Bullet(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/image2/bullet.jpg"));
    this->setScale(GameSetting::BulletScale);
    startTimer(GameSetting::BulletTimer);
}

void Bullet::timerEvent(QTimerEvent *event)
{
    setPos(x(),y()-GameSetting::BulletSpeed);
        if(y()+boundingRect().height()<0){
        scene()->removeItem(this);
        delete this;
    }
}

