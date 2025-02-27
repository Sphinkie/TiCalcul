import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: label.text
    Text {
        id: label
        text: qsTr("Text")
        anchors.fill: parent
        font.pixelSize: 14
        font.bold: false
        color: "black"
    }
}
