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
        color: parent.enabled ? "black" : Universal.chromeDisabledHighColor 
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        font.bold: true
    }

    background: Rectangle {
	id: rec
        color: parent.down ? Universal.chromeHighColor: Universal.chromeMediumColor
        // border.color: Universal.accent
        implicitWidth: 100
        implicitHeight: 80
        radius: 6
    }
}
