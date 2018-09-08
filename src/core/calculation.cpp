
#include "calculation.hpp"

using BBTCalculator::Core::Calculation;

Calculation::Calculation(Loc* l, const RouteList& rList, const BlockList& bList)
    : loc{l}
    , routes{rList}
    , blocks{bList}
{
}

void Calculation::calculateNewBBTEntries(double correctionFactor)
{
    for (const auto& route : routes)
    {
        if (route.isOnlyMainline)
        {
            BBT bbt;

            bbt.route = route.id;
            bbt.fromBlock = route.fromBlock;
            bbt.block = route.toBlock;
            bbt.count = 0;

            bbt.speed = loc->v_cru;

            bbt.steps = 10;

            const double speedMmPerSecond{bbt.speed / 3.6 * 1000};
            const double speedMMPerSecondScaled{speedMmPerSecond /
                                                H0ScalingFactor};

            const QString blockName{bbt.block};
            const auto search = [blockName](const Block& item) {
                return item.name == blockName;
            };

            auto blockIt = std::find_if(blocks.begin(), blocks.end(), search);

            if (blockIt != blocks.end())
            {
                bbt.interval = static_cast<int>(2.0 * blockIt->length /
                                                speedMMPerSecondScaled / bbt.steps * 1000.0);
                bbt.interval = static_cast<int>(bbt.interval * correctionFactor);
            }

            loc->bbt.emplace_back(bbt);
        }
    }
}
