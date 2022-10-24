#ifndef RECTITEM_H
#define RECTITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QColor>

class RectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit RectItem(int number);
    void setHighlight();
    void setNormalMode();
    bool isHighlighted();
    void setPos(int x, int y);
signals:


private:
    const int SIZE;
    const QColor HIGHLIGHT_COLOR, NORMAL_COLOR;
    bool m_isHighlighted;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;


};

#endif // RECTITEM_H
