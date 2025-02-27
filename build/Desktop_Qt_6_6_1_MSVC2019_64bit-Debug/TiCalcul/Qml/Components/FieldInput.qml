import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: input.text
    Rectangle {
        anchors.fill: parent
        color: "#c8e6ca"
        Text {
            id: input
            text: qsTr("Text")
            anchors.fill: parent
            font.pixelSize: 15
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            rightPadding: 8
            font.family: "Courier"
            font.bold: false
            color: "grey"
        }
    }
}
