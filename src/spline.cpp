#include "spline.h"

Spline::Spline()
    : points(QVector<Point2D>()), fTotalSplineLength()
{

}

Point2D Spline::GetSplinePoint(float t, bool bLooped)
{
    int p0, p1, p2, p3;
    if (!bLooped)
    {
        p1 = (int)t + 1;
        if(p1 >= points.size())
        {
            p1 = points.size()-1;
        }
        p2 = p1 + 1;
        if(p2 >= points.size())
        {
            p2 = points.size()-1;
        }
        p3 = p2 + 1;
        if(p3 >= points.size())
        {
            p3 = points.size()-1;
        }
        p0 = p1 - 1;
        if(p0 >= points.size())
        {
            p0 = points.size()-1;
        }
    }
    else
    {
        p1 = (int)t;
        p2 = (p1 + 1) % points.size();
        p3 = (p2 + 1) % points.size();
        p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
    }

    t = t - (int)t;

    float tt = t * t;
    float ttt = tt * t;

    float q1 = -ttt + 2.0f*tt - t;
    float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
    float q3 = -3.0f*ttt + 4.0f*tt + t;
    float q4 = ttt - tt;

    float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
    float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

    return{ tx, ty, 0.0f };
}

Point2D Spline::GetSplineGradient(float t, bool bLooped)
{
    int p0, p1, p2, p3;
    if (!bLooped)
    {
        p1 = (int)t + 1;
        if(p1 >= points.size())
        {
            p1 = points.size()-1;
        }
        p2 = p1 + 1;
        if(p2 >= points.size())
        {
            p2 = points.size()-1;
        }
        p3 = p2 + 1;
        if(p3 >= points.size())
        {
            p3 = points.size()-1;
        }
        p0 = p1 - 1;
        if(p0 >= points.size())
        {
            p1 = points.size()-1;
        }
    }
    else
    {
        p1 = (int)t;
        p2 = (p1 + 1) % points.size();
        p3 = (p2 + 1) % points.size();
        p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
    }

    t = t - (int)t;

    float tt = t * t;

    //Calculate the derivative of the function to find the tangent to the road
    //mathematical formulas
    //f(x) = x => f'(x) = 1
    //f(x) = x^2 => f'(x) = 2x
    //f(x) = x^3 => f'(x) = 3x^2

    float q1 = -3.0f * tt + 4.0f*t - 1;
    float q2 = 9.0f*tt - 10.0f*t;
    float q3 = -9.0f*tt + 8.0f*t + 1.0f;
    float q4 = 3.0f*tt - 2.0f*t;

    float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
    float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

    return{ tx, ty, 0.0f };
}

float Spline::CalculateSegmentLength(int node, bool bLooped)
{
    float fLength = 0.0f;
    float fStepSize = 0.005;

    Point2D old_point, new_point;
    old_point = GetSplinePoint((float)node, bLooped);

    for (float t = 0; t < 1.0f; t += fStepSize)
    {
        new_point = GetSplinePoint((float)node + t, bLooped);
        fLength += sqrtf((new_point.x - old_point.x)*(new_point.x - old_point.x)
                       + (new_point.y - old_point.y)*(new_point.y - old_point.y));
        old_point = new_point;
    }

    return fLength;
}

float Spline::GetNormalisedOffset(float p)
{
    // Which node is the base?
    int i = 0;
    while (p > points[i].length)
    {
        p -= points[i].length;
        i++;
    }

    // The fractional is the offset
    return (float)i + (p / points[i].length);
}

