#ifndef SPLINE_H
#define SPLINE_H
#include <QVector>

struct Point2D
{
    float x;
    float y;
};

struct Spline
{
    QVector<Point2D> points;

    Point2D GetSplinePoint(float t, bool bLooped = false);
    Point2D GetSplineGradient(float t, bool bLooped = false);
};

#endif // SPLINE_H
