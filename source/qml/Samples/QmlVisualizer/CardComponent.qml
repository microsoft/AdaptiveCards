import QtQuick 2.15;
import QtQuick.Layouts 1.3;

ColumnLayout{
    id: cardComponent

    property var card
    signal adaptiveCardButtonClicked(var title, var type, var data)

    Component.onCompleted: reload(CardString);

    function reload(mCard)
    {
        if(card){
            card.destroy()
        }

        card = Qt.createQmlObject(mCard, cardComponent, "card")
        card.buttonClicked.connect(adaptiveCardButtonClicked)
    }
}
