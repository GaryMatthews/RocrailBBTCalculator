
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

            auto getLocList() const -> const LocList&;

        private:
            QDir rootPath;

            std::string planFilePath;

            LocList locList;
        };
    } // namespace Core
} // namespace BBTCalculator