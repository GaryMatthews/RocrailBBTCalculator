
#pragma once

#include "datastructs.hpp"

static const double H0ScalingFactor = 87.0;

namespace BBTCalculator
{
    namespace Core
    {
        class Calculation
        {
        public:
            Calculation(BBTCalculator::Core::Loc& l, BBTCalculator::Core::RouteList& rList, BlockList& bList);

            void caclulateNewBBTEntries();

        private:

            Loc& loc;

            const RouteList& routes;

            const BlockList& blocks;
        };
    } // namespace Core
} // namespace BBTCalculator
