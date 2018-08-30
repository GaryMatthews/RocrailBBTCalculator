

#pragma once

#include <QtCore/QFile>
#include <QtXml/QDomNodeList>

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

            auto getBlockList() const -> BlockList;

        private:

            void parseLocs(const QDomNodeList& locs);

            void parseBlocks(const QDomNodeList& blocks);

            auto convertStringToBool(const QString& string) -> bool;

            LocList locList;

            BlockList blockList;

            QFile file;
        };
    }
}
