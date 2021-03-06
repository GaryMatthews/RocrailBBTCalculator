
#pragma once

#include <memory>

#include <QtCore/QDir>
#include <QtCore/QFile>

#include "datastructs.hpp"

namespace BBTCalculator
{
    namespace Core
    {
        class Workspace
        {
        public:
            void setRootPath(const QDir& root);

            auto getPlanFilePath() const -> const std::string&;

            void setLocList(const LocList& locList);

            auto getLocList() -> LocList&;

            void setBlockList(const BlockList& locList);

            auto getBlockList() -> BlockList&;

            void setRouteList(const RouteList& routeList);

            auto getRouteList() -> RouteList&;

            auto getImagePath() const -> QString;

        private:
            QDir rootPath;

            std::string planFilePath;

            LocList locList;
            BlockList blockList;
            RouteList routeList;
        };
    } // namespace Core
} // namespace BBTCalculator