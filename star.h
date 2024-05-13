#ifndef STAR_H
#define STAR_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Star : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Star(QGraphicsItem* parent=nullptr);
    ~Star(){
       // qDebug()<<"析构Star";
    }

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // STAR_H
