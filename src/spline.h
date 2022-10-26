#ifndef SPLINE_H
#define SPLINE_H
#include <QVector>

struct Point2D
{
    float x;
    float y;
    float length;
};

struct Spline
{
    Spline();

    Point2D GetSplinePoint(float t, bool bLooped = false);
    Point2D GetSplineGradient(float t, bool bLooped = false);
    float CalculateSegmentLength(int node, bool bLooped = false);
    float GetNormalisedOffset(float p);


    QVector<Point2D> points;
    float fTotalSplineLength;
};

#endif // SPLINE_H
