import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: result.text
    Rectangle {
        anchors.fill: parent
        color: Universal.altMediumColor
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
