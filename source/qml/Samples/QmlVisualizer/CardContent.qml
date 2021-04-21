import QtQuick 2.15

Loader{
    id: loader

    asynchronous: true

    source: "CardComponent.qml"

    onLoaded: {
        item.width = width
    }
}
