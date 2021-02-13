import QtQuick 2.15

Loader{
    id: loader

    asynchronous: true
    height: item ? item.implicitHeight : 0

    source: "CardComponent.qml"

    onLoaded: {
        item.width = width
    }
}
