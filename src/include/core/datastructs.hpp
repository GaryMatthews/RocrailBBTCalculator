
#pragma once

#include <QString>
#include <vector>

namespace BBTCalculator
{
    namespace Core
    {
        struct Loc
        {
            QString name = "";
            QString imageName = "";

            bool useBBT{false};
            int bbtSteps{0};

            int v_min{0};
            int v_mid{0};
            int v_cru{0};
        };

        using LocList = std::vector<Loc>;

        struct Block
        {
            QString name = "";

            int length{0};

            // Some blocks have set mainline false but usebbt to true
            bool isMainLine{false};
        };

        using BlockList = std::vector<Block>;
    } // namespace Core
} // namespace BBTCalculator