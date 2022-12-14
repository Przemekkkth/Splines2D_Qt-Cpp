#include "rectitem.h"
#include <QPen>
#include <QBrushData>

const float RectItem::SPEED = 5.0f;

RectItem::RectItem(int number)
    : SIZE(30), HIGHLIGHT_COLOR(Qt::red), NORMAL_COLOR(Qt::yellow), m_isHighlighted(false)
{
    setNormalMode();
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem("1",this);
    text->setText(QString::number(number));
    text->setPos(boundingRect().center() - QPoint(text->boundingRect().width()/2, text->boundingRect().height()/2));
    setPos(100, 100);
    setRect(0, 0, boundingRect().width(), boundingRect().height());
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

void RectItem::setPos(int x, int y)
{
    //Func setPos sets pos for center of rect
    QGraphicsRectItem::setPos(x-boundingRect().width()/2, y - boundingRect().height()/2);
}

QPoint RectItem::pos() const
{
    QPointF p = QGraphicsRectItem::pos();
    p.setX(p.x() + boundingRect().width()/2);
    p.setY(p.y() + boundingRect().height()/2);
    return p.toPoint();
}

QRectF RectItem::boundingRect() const
{
    return QRectF(0,0, SIZE,SIZE);
}
