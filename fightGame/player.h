#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include<QSoundEffect>
class QGraphicsTextItem;

class Player : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem* parent=nullptr);

    // QGraphicsItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    void enemySpawn();
    void gameOver();

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
private:
    bool playing=true;
    QSoundEffect bulletSound;
    QGraphicsTextItem* messageItem=nullptr;
};

#endif // PLAYER_H
