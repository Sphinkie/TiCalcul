import QtQuick
import QtQuick.Controls.Universal

Item {
    property alias text: label.text
    property alias justify: label.horizontalAlignment

    Text {
        id: label
        text: qsTr("Text")
        anchors.fill: parent
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        leftPadding: 8
        rightPadding: 8
        font.pixelSize: 14
        font.bold: true
        color: "black"
    }
}
