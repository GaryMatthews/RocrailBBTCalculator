
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

            bool useBBT;
        };

        using LocList = std::vector<Loc>;
    }
}