

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

            auto getRouteList() const -> RouteList;

            void saveBBTForLocomotive(const Loc& loc);

        private:
            void parseLocs(const QDomNodeList& locs);

            BBTList parseBBT(const QDomNode& node);

            void parseBlocks(const QDomNodeList& blocks);

            void parseRoutes(const QDomNodeList& routes);

            bool isTurnInRoute(const QDomNodeList& switches);

            auto convertStringToBool(const QString& string) -> bool;

            LocList locList;

            BlockList blockList;

            RouteList routeList;

            QFile file;
        };
    } // namespace Core
} // namespace BBTCalculator
