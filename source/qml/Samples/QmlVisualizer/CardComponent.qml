import QtQuick 2.15;
import QtQuick.Layouts 1.3;

ColumnLayout{
    id: cardComponent

    Component.onCompleted: Qt.createQmlObject(CardString, cardComponent, "card")
}
