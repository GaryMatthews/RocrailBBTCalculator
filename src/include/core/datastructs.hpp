
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
            int bbtSteps;

            int v_min;
            int v_mid;
            int v_cru;
        };

        using LocList = std::vector<Loc>;
    }
}