

#include <iostream>
#include <workspace.hpp>

#include "workspace.hpp"

using BBTCalculator::Core::Workspace;

void Workspace::setRootPath(const QDir& root)
{
    rootPath = root;

    planFilePath = rootPath.absoluteFilePath("plan.xml").toStdString();
}

auto Workspace::getPlanFilePath() const -> const std::string&
{
    return planFilePath;
}

void Workspace::setLocList(const BBTCalculator::Core::LocList& lList)
{
    locList = lList;
}

auto Workspace::getLocList() -> BBTCalculator::Core::LocList&
{
    return locList;
}

auto Workspace::getImagePath() const -> QString
{
    return QString(rootPath.absoluteFilePath("images/"));
}
