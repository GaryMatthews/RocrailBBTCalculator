

#include "planparser.hpp"

#include <planparser.hpp>

#include <QtXml/QDomDocument>

#include "datastructs.hpp"

using BBTCalculator::Core::BBTList;
using BBTCalculator::Core::PlanParser;

PlanParser::PlanParser(std::string f)
    : file{QString::fromStdString(f)}
{
    file.open(QIODevice::ReadWrite);
    if (not file.isOpen() or not file.isReadable())
    {
        // TODO: handle error case
    }
}

void PlanParser::parse()
{
    QDomDocument document("plan");
    if (not document.setContent(&file))
    {
        // TODO: report error
        file.close();
    }

    QDomElement root{document.documentElement()};

    QDomNodeList locs = root.elementsByTagName("lc");

    parseLocs(locs);

    QDomNodeList blocks = root.elementsByTagName("bk");

    parseBlocks(blocks);

    QDomNodeList routes = root.elementsByTagName("st");

    parseRoutes(routes);
}

void PlanParser::parseLocs(const QDomNodeList& locs)
{
    locList.reserve(static_cast<unsigned long>(locs.length()));

    for (int i = 0; i < locs.length(); ++i)
    {
        const auto currentLoc = locs.at(i);
        const auto currentLocAttributes{currentLoc.attributes()};

        const QDomAttr locNameAttr{
            currentLocAttributes.namedItem("id").toAttr()};
        const QDomAttr locImagePathAttr{
            currentLocAttributes.namedItem("image").toAttr()};
        const QDomAttr useBBTAttribute{
            currentLocAttributes.namedItem("usebbt").toAttr()};
        const QDomAttr bbtStepsAttribute{
            currentLocAttributes.namedItem("bbtsteps").toAttr()};
        const QDomAttr vMinAttribute{
            currentLocAttributes.namedItem("V_min").toAttr()};
        const QDomAttr vMidAttribute{
            currentLocAttributes.namedItem("V_mid").toAttr()};
        const QDomAttr vCruAttribute{
            currentLocAttributes.namedItem("V_cru").toAttr()};

        Loc loc{locNameAttr.value(),
                locImagePathAttr.value(),
                convertStringToBool(useBBTAttribute.value()),
                bbtStepsAttribute.value().toInt(),
                vMinAttribute.value().toInt(),
                vMidAttribute.value().toInt(),
                vCruAttribute.value().toInt()};

        loc.bbt = parseBBT(currentLoc);

        locList.emplace_back(loc);
    }
}

BBTList PlanParser::parseBBT(const QDomNode& node)
{
    QDomNodeList bbts = node.toElement().elementsByTagName("bbt");

    BBTList bbtList;
    bbtList.reserve(static_cast<unsigned long>(bbts.count()));

    for (int i = 0; i < bbts.count(); ++i)
    {
        const auto currentBBT = bbts.at(i);
        const auto currentBBTAttributes{currentBBT.attributes()};

        const QDomAttr blockAttribute{
            currentBBTAttributes.namedItem("bk").toAttr()};
        const QDomAttr fromBlockAttribute{
            currentBBTAttributes.namedItem("frombk").toAttr()};
        const QDomAttr routeAttribute{
            currentBBTAttributes.namedItem("route").toAttr()};
        const QDomAttr intervalAttribute{
            currentBBTAttributes.namedItem("interval").toAttr()};
        const QDomAttr stepsAttribute{
            currentBBTAttributes.namedItem("steps").toAttr()};
        const QDomAttr speedAttribute{
            currentBBTAttributes.namedItem("speed").toAttr()};
        const QDomAttr blockEnterSideAttribute{
            currentBBTAttributes.namedItem("blockenterside").toAttr()};
        const QDomAttr countAttribute{
            currentBBTAttributes.namedItem("count").toAttr()};
        const QDomAttr fixedAttribute{
            currentBBTAttributes.namedItem("isFixed").toAttr()};

        BBT bbt{blockAttribute.value(),
                fromBlockAttribute.value(),
                routeAttribute.value(),
                intervalAttribute.value().toInt(),
                stepsAttribute.value().toInt(),
                speedAttribute.value().toInt(),
                blockAttribute.value().toInt(),
                countAttribute.value().toInt(),
                convertStringToBool(fixedAttribute.value())};
        bbtList.emplace_back(bbt);
    }
    return bbtList;
}

void PlanParser::parseBlocks(const QDomNodeList& blocks)
{
    blockList.reserve(static_cast<unsigned long>(blocks.length()));

    for (int i = 0; i < blocks.length(); ++i)
    {
        const auto currentBlock = blocks.at(i);
        const auto currentBlockAttributes{currentBlock.attributes()};

        const QDomAttr blockNameAttr{
            currentBlockAttributes.namedItem("id").toAttr()};
        const QDomAttr isMainLineAttribute{
            currentBlockAttributes.namedItem("mainline").toAttr()};
        const QDomAttr blockLenAttribute{
            currentBlockAttributes.namedItem("len").toAttr()};

        Block block{blockNameAttr.value(), blockLenAttribute.value().toInt(),
                    convertStringToBool(isMainLineAttribute.value())};

        blockList.emplace_back(block);
    }
}

void PlanParser::parseRoutes(const QDomNodeList& routes)
{
    routeList.reserve(static_cast<unsigned long>(routes.length()));

    for (int i = 0; i < routes.length(); ++i)
    {
        const auto currentRoute = routes.at(i);
        const auto currentRouteAttributes{currentRoute.attributes()};

        const QDomAttr routeIdAttr{
            currentRouteAttributes.namedItem("id").toAttr()};
        const QDomAttr routeFromBlockAttr{
            currentRouteAttributes.namedItem("bka").toAttr()};
        const QDomAttr routeToBlockAttr{
            currentRouteAttributes.namedItem("bkb").toAttr()};
        const QDomAttr routeFromBlockEnterSideAttr{
            currentRouteAttributes.namedItem("bkaside").toAttr()};
        const QDomAttr routeToBlockEnterSideAttr{
            currentRouteAttributes.namedItem("bkbside").toAttr()};
        const QDomAttr reduceVelocityAttr{
            currentRouteAttributes.namedItem("reducev").toAttr()};

        const QDomNodeList switches{
            currentRoute.toElement().elementsByTagName("swcmd")};

        const bool isCompletelyStraight{not isTurnInRoute(switches)};

        Route route{routeIdAttr.value(),
                    routeFromBlockAttr.value(),
                    routeToBlockAttr.value(),
                    routeFromBlockEnterSideAttr.value(),
                    routeToBlockEnterSideAttr.value(),
                    convertStringToBool(reduceVelocityAttr.value()),
                    isCompletelyStraight};

        routeList.emplace_back(route);
    }
}

bool PlanParser::isTurnInRoute(const QDomNodeList& switches)
{
    if (switches.size() == 0) return false;

    for (int i = 0; i < switches.size(); ++i)
    {
        const auto currentSwitch = switches.at(i);
        const auto currentSwitchAttributes{currentSwitch.attributes()};

        const QDomAttr switchCommand{
            currentSwitchAttributes.namedItem("cmd").toAttr()};

        if (switchCommand.value() == "turnout")
        {
            return true;
        }
    }

    return false;
}

auto PlanParser::getLocList() const -> BBTCalculator::Core::LocList
{
    return locList;
}

auto PlanParser::getBlockList() const -> BBTCalculator::Core::BlockList
{
    return blockList;
}

auto PlanParser::getRouteList() const -> BBTCalculator::Core::RouteList
{
    return routeList;
}

auto PlanParser::convertStringToBool(const QString& string) -> bool
{
    return string.toUpper() == "TRUE";
}
