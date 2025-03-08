import QtQuick
import QtQuick.Controls.Universal

Button {
    id: button
    property string buttonText

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
        implicitWidth: 86
        implicitHeight: 40
        color: button.down ? Universal.foreground.lighter(
                                 1.1) : Universal.foreground
        radius: 6
    }
}
