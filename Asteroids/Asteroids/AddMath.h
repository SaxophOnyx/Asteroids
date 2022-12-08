#pragma once

namespace ast
{
    class AddMath
    {
        public:
        AddMath() = delete;
        AddMath(AddMath&) = delete;
        ~AddMath() = delete;

        static double difference(double a, double b);
    };
}
