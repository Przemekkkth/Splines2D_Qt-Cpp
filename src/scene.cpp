#include "scene.h"
#include <QKeyEvent>

void Scene::drawMarker()
{
    Point2D p1 = path.GetSplinePoint(fMarker, true);
    Point2D g1 = path.GetSplineGradient(fMarker, true);
    //qDebug() << "p1 " << p1.x << "," << p1.y << " g1 " << g1.x << "," << g1.y;
    float r = atan2(-g1.y, g1.x);
    m_markerItem->setLine(25.0f * sin(r) + p1.x, 25.0f * cos(r) + p1.y, -25.0f * sin(r) + p1.x, -25.0f * cos(r) + p1.y);
}

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}, RESOLUTION(1024, 500), FPS(60), SPLIT_SIZE(5), nSelectedPoint(0),
      loopSpeed(int(1000.0f/FPS)), m_leftArrowPressed(false), m_rightArrowPressed(false), m_upArrowPressed(false), m_downArrowPressed(false),
      m_aKeyPressed(false), m_sKeyPressed(false), fMarker(0.0f)
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

    m_markerItem = new QGraphicsLineItem();
    addItem(m_markerItem);
    QPen markerPen;
    markerPen.setBrush(QColor(Qt::blue));
    markerPen.setWidth(5);
    m_markerItem->setPen(markerPen);
    drawMarker();
}

void Scene::clearSplines()
{
    if(m_splitPoints.size())
    {
        m_splitPoints.clear();
    }
    if(m_splineRects.size())
    {
        for(int i = 0; i < m_splineRects.size(); ++i)
        {
            removeItem(m_splineRects[i]);
        }
    }
    m_splineRects.clear();

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
            m_splineRects.push_back(rItem);
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
        case Qt::Key_A:
        {
            m_aKeyPressed = true;
        }
            break;
        case Qt::Key_S:
        {
            m_sKeyPressed = true;
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
    case Qt::Key_A:
    {
        m_aKeyPressed = false;
    }
        break;
    case Qt::Key_S:
    {
        m_sKeyPressed = false;
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
        if(m_leftArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(-RectItem::SPEED, 0);
            path.points[nSelectedPoint].x = rectItems[nSelectedPoint]->pos().x();
            path.points[nSelectedPoint].y = rectItems[nSelectedPoint]->pos().y();
            clearSplines();
            drawSpline();
        }
        else if(m_rightArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(+RectItem::SPEED, 0);
            path.points[nSelectedPoint].x = rectItems[nSelectedPoint]->pos().x();
            path.points[nSelectedPoint].y = rectItems[nSelectedPoint]->pos().y();
            clearSplines();
            drawSpline();
        }
        else if(m_upArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(0, -RectItem::SPEED);
            path.points[nSelectedPoint].x = rectItems[nSelectedPoint]->pos().x();
            path.points[nSelectedPoint].y = rectItems[nSelectedPoint]->pos().y();
            clearSplines();
            drawSpline();
        }
        else if(m_downArrowPressed)
        {
            rectItems[nSelectedPoint]->moveBy(0, +RectItem::SPEED);
            path.points[nSelectedPoint].x = rectItems[nSelectedPoint]->pos().x();
            path.points[nSelectedPoint].y = rectItems[nSelectedPoint]->pos().y();
            clearSplines();
            drawSpline();
        }

        if(m_aKeyPressed)
        {
            fMarker -= 0.05f;
        }
        else if(m_sKeyPressed)
        {
            fMarker += 0.05f;
        }

        if (fMarker >= (float)path.points.size())
        {
            fMarker -= (float)path.points.size();
        }

        if (fMarker < 0.0f)
        {
            fMarker += (float)path.points.size();
        }

        drawMarker();
    }
}
