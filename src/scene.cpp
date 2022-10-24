#include "scene.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}, RESOLUTION(1024, 500), FPS(60), SPLIT_SIZE(10), nSelectedPoint(0),
      loopSpeed(int(1000.0f/FPS))
{
    setSceneRect(0,0, RESOLUTION.width(), RESOLUTION.height());
    loopTime = 0.0f;
    deltaTime = 0.0f;

//    path.points = { { 5, 25 },{ 15, 25 },{ 25, 25 },{ 35, 25 },{ 45, 25 },{ 55, 25 },{ 65, 25 },{ 75, 25 },{ 85, 25 },{ 95, 25 } };

    path.points = { { 5, 25 },{ 15, 20 }, { 25, 25 }};//,{ 35, 25 },{ 45, 25 },{ 55, 25 },{ 65, 25 },{ 75, 25 },{ 85, 25 },{ 95, 25 } };


    for(int i = 0; i < path.points.size(); ++i)
    {
        RectItem* rI = new RectItem(i);
        addItem(rI);
        rI->setPos(path.points[i].x*10, path.points[i].y*10);
        qDebug() << rI->pos();
        rectItems.append(rI);
    }

    if(rectItems.size())
    {
        rectItems[nSelectedPoint]->setHighlight();
    }


    connect(&timer, &QTimer::timeout, this, &Scene::loop);
    timer.start(int(1000.0f/FPS));
    elapsedTimer.start();
    setBackgroundBrush(QBrush(Qt::black));
    drawSpline();
}

void Scene::drawSpline()
{
    for (float t = 0; t < (float)path.points.size(); t += 0.005f)
    {
        Point2D pos = path.GetSplinePoint(t, true);
        if(!m_splitPoints.contains(QPoint(int(pos.x)*10, int(pos.y)*10)))
        {
            m_splitPoints.push_back(QPoint(int(pos.x)*10, int(pos.y)*10));
            QGraphicsRectItem* rItem = new QGraphicsRectItem(-SPLIT_SIZE/2, -SPLIT_SIZE/2, SPLIT_SIZE, SPLIT_SIZE);
            qDebug() << "x " << int(pos.x) << " y " << int(pos.y);
            rItem->setPos(int(pos.x), int(pos.y));
            rItem->setBrush(QBrush(QColor(Qt::white)));
            rItem->setPen(QPen(QColor(Qt::white)));
            addItem(rItem);


        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        switch (event->key()) {
        case Qt::Key_Z:
        {
            rectItems[nSelectedPoint]->setNormalMode();
            nSelectedPoint++;
            if (nSelectedPoint >= path.points.size())
            {
                nSelectedPoint = 0;
            }
            rectItems[nSelectedPoint]->setHighlight();
        }
            break;
        case Qt::Key_X:
        {
            rectItems[nSelectedPoint]->setNormalMode();
            nSelectedPoint--;
            if (nSelectedPoint < 0)
            {
                nSelectedPoint = path.points.size() - 1;
            }
            rectItems[nSelectedPoint]->setHighlight();
        }
            break;
        }
    }
}

void Scene::loop()
{
    deltaTime = elapsedTimer.elapsed();
    elapsedTimer.restart();

    loopTime += deltaTime;
    if( loopTime > loopSpeed)
    {
        loopTime -= loopSpeed;
        //qDebug() << "loop()";
    }
}
