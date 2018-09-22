
#include "calculation.hpp"

using BBTCalculator::Core::Calculation;
using BBTCalculator::Core::Loc;
using BBTCalculator::Core::BlockList;
using BBTCalculator::Core::RouteList;

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
        BBT bbt;

        bbt.route = route.id;
        bbt.fromBlock = route.fromBlock;
        bbt.block = route.toBlock;
        bbt.count = 0;

        if (route.isOnlyMainline)
        {
            bbt.speed =
                !route.shallReduceVelocity
                    ? loc->v_cru
                    : route.isCompletelyStraight ? loc->v_cru : loc->v_mid;
        }
        else
        {
            bbt.speed = loc->v_mid;
        }
        bbt.steps = loc->bbtSteps;

        const double speedMmPerSecond{(bbt.speed - loc->v_min) / 3.6 * 1000};
        const double speedMMPerSecondScaled{speedMmPerSecond / H0ScalingFactor};

        const QString blockName{bbt.block};
        const auto search = [blockName](const Block& item) {
            return item.name == blockName;
        };

        auto blockIt = std::find_if(blocks.begin(), blocks.end(), search);

        if (blockIt != blocks.end())
        {
            bbt.interval =
                static_cast<int>(2.0 * blockIt->length /
                                 speedMMPerSecondScaled / bbt.steps * 1000.0);
            bbt.interval = static_cast<int>(bbt.interval * correctionFactor);
        }

        loc->bbt.emplace_back(bbt);
    }
}
