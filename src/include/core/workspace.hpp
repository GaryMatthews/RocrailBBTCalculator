
#pragma once

#include <QtCore/QDir>

namespace BBTCalculator
{
    namespace Core
    {
        class Workspace
        {
        public:
            void setRootPath(const QDir& root);

        private:
            QDir rootPath;
        };
    } // namespace Core
} // namespace BBTCalculator