#include "Vector2.h"
#include <cmath>

namespace ast
{
    Vector2::Vector2()
        : x(0.f), y(0.f)
    {

    }

    Vector2::Vector2(double x, double y)
        : x(x), y(y)
    {

    }

    Vector2::Vector2(double ax, double ay, double bx, double by)
    {
        if (bx > ax)
            x = std::fmax(ax, bx) - std::fmin(ax, bx);
        else
            x = (std::fmax(ax, bx) - std::fmin(ax, bx)) * -1;

        if (by > ay)
            y = std::fmax(ay, by) - std::fmin(ay, by);
        else
            y = (std::fmax(ay, by) - std::fmin(ay, by)) * -1;
    }

    double Vector2::calcLength()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    void Vector2::normalize()
    {
        double len = calcLength();
        x = x / len;
        y = y / len;
    }
}
