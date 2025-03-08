import QtQuick
import QtQuick.Controls.Universal

Button {
    property string fieldText

    contentItem: Text {
        id: input // utile ?
        text: fieldText
        // color: button.down ? "black" : "white"
        anchors.fill: parent // utile ?
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        rightPadding: 8 // utile ?
        font.pixelSize: 15
        font.family: "Courier"
        font.bold: false
        color: "grey"
    }

    background: Rectangle {
        anchors.fill: parent // utile ?
        implicitWidth: 400
        implicitHeight: 40
        color: "#c8e6ca"
    }
}
