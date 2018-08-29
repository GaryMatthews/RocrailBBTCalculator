

#pragma once

#include <QtCore/QFile>

#include "datastructs.hpp"

namespace BBTCalculator
{
    namespace Core
    {
        class PlanParser
        {
        public:
            explicit PlanParser(std::string filePath);

            void parse();

            auto getLocList() const -> LocList;

        private:

            LocList locList;

            QFile file;
        };
    }
}
