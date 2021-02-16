import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "qrc:/"

Item {
    id: delegate
    readonly property var listView: parent.ListView.view

    height: mainLayout.height
    width: listView.width

    GridLayout{
        id: mainLayout

        readonly property int margins: 10
        width: parent.width
        columns: 1

        Rectangle{
            id: frame
            color: "grey"
            radius: 8
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            Layout.margins: parent.margins
            Layout.preferredHeight: cardLayout.height

            ColumnLayout{
                id: cardLayout
                width: delegate.width - 2*mainLayout.margins

                CardContent {
                    id: cardContentLoader
                    Layout.fillWidth: true
                    Layout.margins: 5
                    Layout.preferredHeight: item ? item.height : 25
                }
            }
        }
    }
}
