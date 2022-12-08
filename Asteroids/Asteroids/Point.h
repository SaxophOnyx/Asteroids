#pragma once

namespace ast
{
    struct Point
    {
        Point();
        Point(double x, double y);
        Point(Point&) = delete;
        virtual ~Point() = default;

        double distance(const Point& p) const;

        double x;
        double y;
    };
}
