#include "Point.h"
#include <cmath>

namespace ast
{
    Point::Point()
        : x(0.f), y(0.f)
    {

    }

    Point::Point(double x, double y)
        : x(x), y(y)
    {

    }

    double Point::distance(const Point& p) const
    {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));;
    }
}
