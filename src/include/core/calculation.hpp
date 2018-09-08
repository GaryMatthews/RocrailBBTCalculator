
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
            Calculation(Loc* l, const RouteList& rList, const BlockList& bList);

            void calculateNewBBTEntries(double correctionFactor);

        private:

            Loc* loc;

            const RouteList& routes;

            const BlockList& blocks;
        };
    } // namespace Core
} // namespace BBTCalculator
