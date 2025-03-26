import QtQuick
import QtQuick.Controls.Universal


/* ****************************************************************************************
 * Le type KeyboardKeyForm fournit un bouton customisé pour les touches du clavier virtuel.
 * Les clickes sur les bourton sont gérés par le controlleur parent Keyboard.
 ****************************************************************************************** */
Button {
    id: button
    property string buttonText
    property alias texte: texte

    display: AbstractButton.TextOnly

    contentItem: Text {
        id: texte
        text: buttonText
        color: parent.enabled ? "black" : Universal.chromeDisabledHighColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        font.bold: true
    }

    background: Rectangle {
        id: rec
        color: parent.down ? Universal.chromeHighColor : Universal.chromeMediumColor
        implicitWidth: 100
        implicitHeight: 80
        radius: 6
    }
}
