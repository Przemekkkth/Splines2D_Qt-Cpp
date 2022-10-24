#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include "scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View();

private:
    Scene* m_scene;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
