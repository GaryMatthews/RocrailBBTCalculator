
#pragma once

#include <vector>

#include <QString>

namespace BBTCalculator
{
    namespace Core
    {
        struct Loc
        {
            QString name = "";
            QString imageName = "";
        };

        using LocList = std::vector<Loc>;
    }
}