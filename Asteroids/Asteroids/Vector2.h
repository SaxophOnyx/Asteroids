#pragma once

namespace ast
{
    class Vector2
    {
        public:
        Vector2();
        Vector2(double x, double y);
        Vector2(double ax, double ay, double bx, double by);
        Vector2(Vector2&) = delete;
        virtual ~Vector2() = default;

        double calcLength();
        void normalize();

        double x;
        double y;
    };
}
