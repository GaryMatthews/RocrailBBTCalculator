

#include "planparser.hpp"

#include <QtXml/QDomDocument>
#include <planparser.hpp>

#include "datastructs.hpp"

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

        Loc loc{locNameAttr.value(), locImagePathAttr.value(),
                convertStringToBool(useBBTAttribute.value()),
                bbtStepsAttribute.value().toInt(),
                vMinAttribute.value().toInt(),
                vMidAttribute.value().toInt(),
                vCruAttribute.value().toInt()};

        locList.emplace_back(loc);
    }
}

auto PlanParser::getLocList() const -> BBTCalculator::Core::LocList
{
    return locList;
}

auto PlanParser::convertStringToBool(const QString& string) -> bool
{
    return string.toUpper() == "TRUE";
}
