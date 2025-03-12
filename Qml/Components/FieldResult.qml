import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: result.text

    Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        color: Universal.altMediumColor

        Text {
            id: result
            text: "result"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            leftPadding: 8
            font.pixelSize: 15
            font.family: "Courier"
            font.bold: true
            color: Universal.chromeAltLowColor
        }
    }


    /*
    Label {
        id: result
        anchors.fill: parent
        text: "result"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        font.family: "Courier"
        font.bold: true
        color: Universal.chromeAltLowColor

        background: Rectangle {
            color: "red"
            // Universal.altMediumColor
        }
    }*/
}
