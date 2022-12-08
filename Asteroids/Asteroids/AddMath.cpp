#include "AddMath.h"

namespace ast
{
    double AddMath::difference(double a, double b)
    {
        if (a >= b)
            return a - b;
        else
            return (b - a);
    }
}
