#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QSize>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsLineItem>
#include "rectitem.h"
#include "spline.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:


private:
    void clearSplines();
    const QSize RESOLUTION;
    const int FPS;
    const int SPLIT_SIZE;
    QVector<RectItem*> rectItems;
    QVector<QGraphicsRectItem*> m_splineRects;
    Spline path;
    int nSelectedPoint;
    QElapsedTimer elapsedTimer;
    QTimer timer;
    float deltaTime, loopTime;
    const float loopSpeed;
    void drawSpline();
    QVector<QPoint> m_splitPoints;
    bool m_leftArrowPressed, m_rightArrowPressed, m_upArrowPressed, m_downArrowPressed;
    bool m_aKeyPressed, m_sKeyPressed;
    float fMarker;
    QGraphicsLineItem* m_markerItem;
    void drawMarker();

private slots:
    void loop();
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
