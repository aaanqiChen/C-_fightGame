#include "score.h"
#include<QFont>
#include"GameSetting.h"

Score::Score(QGraphicsItem *parent):QGraphicsTextItem{parent} {
    reset();
}

void Score::reset()
{
    score=0;
    setPlainText("分 数："+QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Courier New",GameSetting::FontSize,QFont::Bold));
}

void Score::increase()
{
    ++score;
    ++score;
    setPlainText("分 数："+QString::number(score));
}
void Score::decrease()
{
    --score;
    setPlainText("分 数："+QString::number(score));
}
