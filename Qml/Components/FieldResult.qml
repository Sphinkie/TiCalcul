import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: result.text
    property alias color: bg.color
    implicitWidth: 120
    implicitHeight: 40

    Rectangle {
        id: bg
        color: Universal.altMediumColor
        anchors.fill: parent

        Text {
            id: result
            text: "result"
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            leftPadding: 8
            font.pixelSize: 15
            font.family: "Courier"
            font.bold: true
            color: Universal.chromeAltLowColor
        }
    }
}
