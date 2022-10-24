#include "view.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>

View::View()
    : m_scene(new Scene(this))
{
    setScene(m_scene);
    resize(m_scene->sceneRect().width()+2, m_scene->sceneRect().height()+2);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
        case Qt::Key_Escape:
    {
        QApplication::instance()->quit();
    }
        break;
    }

    QGraphicsView::keyPressEvent(event);
}
