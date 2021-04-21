import QtQuick 2.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Row{
    id: root
    padding: 10
    spacing: 5
	width : 1330
	height : 800

    Loader{
        id: cardListViewLoader
        source: "SampleCardListView.qml"
		height : parent.height - 20
    }

    Loader{
        id: cardEditorLoader
        source: "CardEditor.qml"
		height : parent.height - 20
    }

    Rectangle{
        id: cardRoot

        height: parent.height - 20
		width : parent.width - 680
        color: 'lightblue'
        radius: 8
        border.width: 2
        border.color: 'black'

        Rectangle{
            height : parent.height - 20
            width: parent.width - 20
            radius: 8
            x: 10;y: 10
            color: "transparent"


            ListModel{
                id: cardModel
                Component.onCompleted: {
                    append({"CardString": _aQmlCard });
                }
            }

            Component{
                id: delegate
                Loader{
                    id: loader
                    source: "AdaptiveCardItemDelegate.qml"

                    onLoaded: {
                        cardEditorLoader.item.reloadCard.connect(loader.item.reloadCard)
                        cardListViewLoader.item.reloadCard.connect(loader.item.reloadCard)
                        loader.item.adaptiveCardButtonClicked.connect(root.onAdaptiveCardButtonClicked)
                    }
                }
            }

            ListView{
                id: cardsList
                anchors.fill: parent
                cacheBuffer: 10000
                delegate: delegate
                model: cardModel
                clip: true
            }
        }
    }

    Loader{
        id: cardOutputLoader
        source: "CardOutput.qml"
    }

    Component.onCompleted: {
        cardListViewLoader.item.listItemClicked.connect(cardEditorLoader.item.setCardEditor)        
    }

    Connections {
        target: _aModel

        onSendCardResponseToQml: {
            cardOutputLoader.item.output = output
        }
    }

    function onAdaptiveCardButtonClicked(title, type, data){
        _aModel.onAdaptiveCardButtonClicked(title, type, data)
        cardOutputLoader.item.open()
    }
}
