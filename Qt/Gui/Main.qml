import QtQuick
import QtQuick.Controls 2.15

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        id: button
        text: qsTr("Button")
        anchors.fill: parent
        topPadding: 0
    }
}
