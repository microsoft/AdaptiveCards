import QtQuick 2.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id: cardEditor
    width: 400
    height: 800
    color: 'lightblue'
    border.color: 'black'
    border.width: 2
    radius: 8
    
    signal reloadCard(var card)
    
    Column{
        id: cardEditorLayout
        anchors.fill: parent
        padding: 5
        spacing: 10
        
        ScrollView{
            width: 390
            height: cardEditorLayout.height - cardEditorLayout.spacing - 2*cardEditorLayout.padding - renderButton.height
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
                
                placeholderText:"enter card json";
            }
        }
        
        Button{
            id: renderButton
            height: 50
            width: 390
            
            text: "Render"
            
            onClicked: {
                reloadCard(_aModel.generateQml(multilineInputId.text))
            }
        }
    }
    
    function setCardEditor(index, json){
        multilineInputId.text = json
    }
    
    Connections {
        target: _aModel
        
        onReloadCardOnThemeChange: {
            reloadCard(_aModel.generateQml(multilineInputId.text))
        }
    }
}
