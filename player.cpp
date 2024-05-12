#include "player.h"
#include<QPixmap>
#include"GameSetting.h"
#include<QKeyEvent>
#include"enemy.h"
#include"stone.h"
#include"bullet.h"
#include<QGraphicsScene>
#include"health.h"
#include"score.h"
#include<QGraphicstextItem>
#include<QFontMetrics>
using namespace GameSetting;
Player::Player(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    bulletSound.setSource(QUrl(""));
    setPixmap(QPixmap(":/image2/flight.jpg"));
    setScale(PlayerScale);
    setPos(SceneWidth/2-boundingRect().width()*PlayerScale/2,
           SceneHeight-boundingRect().height()*PlayerScale);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    startTimer(500);
}


void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
        if(pos().x()>0)
            setPos(x()-PlayerMoveSpeed,y());
        break;
    case Qt::Key_Right:
        if(pos().x()<SceneWidth-boundingRect().width()*PlayerScale)
            setPos(x()+PlayerMoveSpeed,y());
        break;
    case Qt::Key_S:
        if(playing) return;
        playing=true;
        Health::getInstance().reset();
        Score::getInstance().reset();
        messageItem->hide();
        break;
    case Qt::Key_Space:
         bulletSound.play();
        Bullet* bullet=new Bullet;
        int temp=x()+boundingRect().width()*PlayerScale/2;//只考虑子弹的宽度
        temp-=bullet->boundingRect().width()*BulletScale/2;//向左移动半个子弹的宽度
        bullet->setPos(temp,y());
        scene()->addItem(bullet);
        //播放音效
    }
}

void Player::enemySpawn()
{
    Enemy* enemy=new Enemy;
    scene()->addItem(enemy);
}

void Player::stoneSpawn()
{
    Stone* stone=new Stone;
    scene()->addItem(stone);
}

void Player::gameOver()
{
    playing=false;
    for(auto item:scene()->items()){
        if(typeid(*item)==typeid(Enemy)){
            scene()->removeItem(item);
            delete item;
        }
    }
    for(auto item:scene()->items()){
        if(typeid(*item)==typeid(Stone)){
            scene()->removeItem(item);
            delete item;
        }
    }
    if(!messageItem){
        messageItem=new QGraphicsTextItem;
        scene()->addItem(messageItem);
        QString message("Game Over!按s键重新开始");
            messageItem->setPlainText(message);
        messageItem->setDefaultTextColor(Qt::black);
        QFont font("Courier New",GameSetting::FontSize*2,QFont::Bold);
        messageItem->setFont(font);
        QFontMetrics fm(font);
        int msgWidth=fm.horizontalAdvance(message);
        messageItem->setPos(GameSetting::SceneWidth/2-msgWidth/2,
                            GameSetting::SceneHeight/2);
    }
    else {
        messageItem->show();
    }
}


void Player::timerEvent(QTimerEvent *)
{
    if(playing){
    enemySpawn();
    stoneSpawn();
    }
    if(Health::getInstance().getHealth()<=0){
        gameOver();
    }
}
