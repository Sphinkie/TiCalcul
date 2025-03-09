import QtQuick
import QtQuick.Controls.Universal
import TiCalcul

Button {
    required property Afficheur afficheur

    contentItem: Text {
        text: afficheur.displayValue
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
        //color: parent.pressed ? "white" : "#c8e6ca"
        color: (afficheurActif.name == afficheur) ? "white" : "#c8e6ca"
    }
}
