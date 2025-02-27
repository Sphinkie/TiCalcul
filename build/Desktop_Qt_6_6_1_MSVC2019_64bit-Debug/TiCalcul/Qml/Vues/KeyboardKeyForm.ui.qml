import QtQuick
import QtQuick.Controls
import "../Components"

// On customise un Button avec deux propriétés : Display et Background
Button {
    id: button
    //    property alias buttonText: button.text
    property string buttonText

    display: AbstractButton.TextOnly
    text: buttonText
    font.pointSize: 16
    font.bold: true

    background: Rectangle {
        //color: "#8bc34a" // TiStyle.buttonIdleColor
        //border.color: TiStyle.buttonPressedColor
        implicitWidth: 100
        implicitHeight: 80
        radius: 6
    }
}
