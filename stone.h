#ifndef STONE_H
#define STONE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Stone : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Stone(QGraphicsItem* parent=nullptr);
    ~Stone(){
        qDebug()<<"析构Enemy";
    }

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // STONE_H
