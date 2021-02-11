import QtQuick 2.15
import QtQuick.Window 2.2

Item {
    id: root
    width: 600
    height: 600

    Rectangle {
        id: cardArea
        width: 600
        height: 80
        color: "lightgrey"
        anchors.centerIn: root
        Component.onCompleted: root.createItem();
    }

    function createItem() {
        Qt.createQmlObject(_aQmlCard, cardArea, "dynamicItem");
    }
}
