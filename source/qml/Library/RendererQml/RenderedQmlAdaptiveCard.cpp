#include "pch.h"

#include "RenderedQmlAdaptiveCard.h"

namespace RendererQml
{
    RenderedQmlAdaptiveCard::RenderedQmlAdaptiveCard(std::shared_ptr<QmlTag> qmlTag, std::shared_ptr<AdaptiveCards::AdaptiveCard> originatingCard, const std::vector<AdaptiveWarning>& warnings) :
        RenderedQmlAdaptiveCardBase(originatingCard, warnings), m_qml(qmlTag)
    {
    }

    std::shared_ptr<QmlTag> RenderedQmlAdaptiveCard::GetResult()
    {
        return m_qml;
    }

    //std::string RenderedQmlAdaptiveCard::GetResult()
    //{
    //    /*const std::string QmlCard = "import QtQuick 2.15; Item { id: root; anchors.fill: parent; Text { id: txt1; text: qsTr(\"color: default\"); anchors { left: parent.left; top: parent.top; right: parent.right; } color: \"black\"; font.pointSize: 12; } Text { id: txt2; text: qsTr(\"color: accent\"); anchors { left: parent.left; top: txt1.bottom; right: parent.right; } color: \"blue\"; font.pointSize: 12; } Text { id: txt3; text: qsTr(\"color: good\"); anchors { left: parent.left; top: txt2.bottom; right: parent.right; } color: \"green\"; font.pointSize: 12; } Text { id: txt4; text: qsTr(\"color: attention\"); anchors { left: parent.left; top: txt3.bottom; right: parent.right; } color: \"red\"; font.pointSize: 12; } }";*/

    //    const std::string QmlCard = "import QtQuick 2.15; import QtQuick.Layouts 1.3; Item { id: adaptiveCardItem; property int padding: 20; anchors.fill: parent; ColumnLayout { id: adaptiveCardLayout; anchors.fill: parent; Rectangle { id: adaptiveCardRectangle; color: 'yellow'; Layout.margins: padding; Layout.fillWidth: true; Layout.preferredHeight: 40; } } }";

    //    return QmlCard;
    //}
}
