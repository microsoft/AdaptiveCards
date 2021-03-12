import QtQuick 2.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Popup {
    id: popup

    property string output: ""

    x: 300
    y: 100
    width: 300
    height: 500
    padding: 0
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent | Popup.CloseOnPressOutside

    Rectangle{
        id: cardOutput
        anchors.fill: parent
        color: 'lightblue'
        border.color: 'black'
        border.width: 2

        Column{
            id: cardOutputLayout
            anchors.fill: parent
            padding: 5
            spacing: 10

            ScrollView{
                width: 290
                height: cardOutputLayout.height - cardOutputLayout.spacing
                ScrollBar.vertical.interactive:true;

                TextArea{
                    id:multilineInputId;
                    wrapMode:Text.Wrap;
                    font.pixelSize:14;
                    selectByMouse: true

                    background:Rectangle{
                        radius:8;
                        color:multilineInputId.hovered ? 'lightgray' : 'white';
                        border.color:multilineInputId.activeFocus? 'black' : 'grey';
                        border.width:1;
                        layer.enabled:multilineInputId.activeFocus ? true : false;

                    }

                    enabled: false

                    placeholderText:"Card output window!";
                    text: output
                }
            }
        }
    }
}
