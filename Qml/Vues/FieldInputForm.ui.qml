import QtQuick
import QtQuick.Controls.Universal

Button {
    property string fieldText

    contentItem: Text {
        text: fieldText
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        // rightPadding: 8 // utile ?
        font.pixelSize: 15
        font.family: "Courier"
        font.bold: false
        color: "grey"
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40
        color: parent.pressed ? "white" : "#c8e6ca"
    }
}
