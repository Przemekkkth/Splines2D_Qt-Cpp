#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QSize>
#include <QTimer>
#include <QElapsedTimer>
#include "rectitem.h"
#include "spline.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:


private:
    const QSize RESOLUTION;
    const int FPS;
    const int SPLIT_SIZE;
    QVector<RectItem*> rectItems;
    Spline path;
    int nSelectedPoint;
    QElapsedTimer elapsedTimer;
    QTimer timer;
    float deltaTime, loopTime;
    const float loopSpeed;
    void drawSpline();
    QVector<QPoint> m_splitPoints;
private slots:
    void loop();
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENE_H