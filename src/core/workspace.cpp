

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

void Workspace::setLocList(const LocList& lList)
{
    locList = lList;
}

auto Workspace::getLocList() -> LocList&
{
    return locList;
}

void Workspace::setBlockList(const BlockList& lList)
{
    blockList = lList;
}

auto Workspace::getBlockList() -> BlockList&
{
    return blockList;
}

auto Workspace::getImagePath() const -> QString
{
    return QString(rootPath.absoluteFilePath("images/"));
}
