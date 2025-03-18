import QtQuick
import QtQuick.Controls.Universal

Button {
    id: control
    text: "Button"
	property color color

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.down ? "white" : Universal.baseMediumLowColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 40
		color: control.color
    }
}
