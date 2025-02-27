import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: input.text
    Text {
        id: input
        text: qsTr("Text")
        anchors.fill: parent
        font.pixelSize: 15
        font.bold: false
        color: "grey"
    }
}
