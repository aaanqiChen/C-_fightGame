#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>
#include"GameSetting.h"

class Health : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Health(QGraphicsItem* parent=nullptr);
    int getHealth(){return health;}
    void decrease();
    void reset();
    static Health& getInstance(){
        static Health obj;
        return obj;
    }
private:
    int health=GameSetting::HealthStart;
};

#endif // HEALTH_H
