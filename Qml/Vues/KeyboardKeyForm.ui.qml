import QtQuick
import QtQuick.Controls.Universal


/*!
  * Le type KeyboardForm fournit un bouton customisé pour les touches du clavier virtuel.
  */
Button {
    id: button
    property string buttonText

    display: AbstractButton.TextOnly

    contentItem: Text {
        text: buttonText
        // color: button.down ? "black" : "white"
        color: "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        font.bold: true
    }

    background: Rectangle {
        color: button.down ? "#d0d0d0" : "#e0e0e0"
        // border.color: "purple"
        implicitWidth: 100
        implicitHeight: 80
        radius: 6
    }
}
