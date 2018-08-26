
#pragma once

#include <QtCore/QDir>

namespace BBTCalculator::Core
{
    class Workspace
    {
    public:
        void setRootPath(const QDir& root);
    private:
        QDir rootPath;
    };
}

