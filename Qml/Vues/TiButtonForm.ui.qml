import QtQuick
import QtQuick.Controls.Universal


Button {
    id: button
    anchors.fill: parent
    anchors.topMargin: 8

    contentItem: Text {
        text: buttonText
        // color: button.down ? "black" : "white"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
        font.bold: false
        //font.letterSpacing: 2
    }

    background: Rectangle {
        color: button.down ? Universal.foreground.lighter(
                                 1.1) : Universal.foreground
        radius: 6
    }
}
