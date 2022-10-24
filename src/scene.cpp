#include "scene.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}, RESOLUTION(1024, 500), FPS(60), SPLIT_SIZE(5), nSelectedPoint(0),
      loopSpeed(int(1000.0f/FPS)), m_leftArrowPressed(false), m_rightArrowPressed(false), m_upArrowPressed(false), m_downArrowPressed(false)
{
    setSceneRect(0,0, RESOLUTION.width(), RESOLUTION.height());
    loopTime = 0.0f;
    deltaTime = 0.0f;

    //    path.points = { { 5, 25 },{ 15, 25 },{ 25, 25 },{ 35, 25 },{ 45, 25 },{ 55, 25 },{ 65, 25 },{ 75, 25 },{ 85, 25 },{ 95, 25 } };

    path.points = { { 50, 250 },{ 150, 200 }, { 250, 200} ,{ 350, 250 }};//,{ 55, 25 },{ 65, 25 },{ 75, 25 },{ 85, 25 },{ 95, 25 } };


    for(int i = 0; i < path.points.size(); ++i)
    {
        RectItem* rI = new RectItem(i);
        addItem(rI);
        rI->setPos(path.points[i].x, path.points[i].y);
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
        if(!m_splitPoints.contains(QPoint(int(pos.x), int(pos.y))))
        {
            m_splitPoints.push_back(QPoint(int(pos.x), int(pos.y)));
            QGraphicsRectItem* rItem = new QGraphicsRectItem(-SPLIT_SIZE/2, -SPLIT_SIZE/2, SPLIT_SIZE, SPLIT_SIZE);
            rItem->setZValue(-1);
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
    else
    {
        switch (event->key()) {
        case Qt::Key_Left:
        {
            m_leftArrowPressed = true;
        }
            break;
        case Qt::Key_Right:
        {
            m_rightArrowPressed = true;
        }
            break;
        case Qt::Key_Up:
        {
            m_upArrowPressed = true;
        }
            break;
        case Qt::Key_Down:
        {
            m_downArrowPressed = true;
        }
            break;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    {
        m_leftArrowPressed = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightArrowPressed = false;
    }
        break;
    case Qt::Key_Up:
    {
        m_upArrowPressed = false;
    }
        break;
    case Qt::Key_Down:
    {
        m_downArrowPressed = false;
    }
        break;
    }

    QGraphicsScene::keyReleaseEvent(event);
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
        if(m_leftArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(-RectItem::SPEED, 0);
        }
        else if(m_rightArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(+RectItem::SPEED, 0);
        }
        else if(m_upArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(0, -RectItem::SPEED);
        }
        else if(m_downArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(0, +RectItem::SPEED);
        }
    }
}
