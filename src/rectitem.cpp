#include "rectitem.h"
#include <QPen>
#include <QBrushData>
RectItem::RectItem(int number)
    : SIZE(30), HIGHLIGHT_COLOR(Qt::red), NORMAL_COLOR(Qt::yellow), m_isHighlighted(false)
{
    setNormalMode();
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem("1",this);
    text->setText(QString::number(number));
    text->setPos(QPoint(0,0)-QPoint(text->boundingRect().width()/2, text->boundingRect().height()/2));
    setPos(100, 100);
    setRect(-boundingRect().width()/2, -boundingRect().height()/2, boundingRect().width(), boundingRect().height());
}

void RectItem::setHighlight()
{
    m_isHighlighted = true;
    setPen(QPen(HIGHLIGHT_COLOR));
    setBrush(QBrush(HIGHLIGHT_COLOR));
}

void RectItem::setNormalMode()
{
    m_isHighlighted = false;
    setPen(QPen(NORMAL_COLOR));
    setBrush(QBrush(NORMAL_COLOR));
}

bool RectItem::isHighlighted()
{
    return m_isHighlighted;
}

QRectF RectItem::boundingRect() const
{
    return QRectF(0,0, SIZE,SIZE);
}
