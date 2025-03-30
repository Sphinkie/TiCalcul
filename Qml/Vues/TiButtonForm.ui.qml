import QtQuick
import QtQuick.Controls.Universal


/* ***********************************************************************************
 * \brief Le type TiButton offre des boutons customisés au niveau des couleurs,
 *        de l'arrondi, et de la police.
 **************************************************************************************/
Button {
    id: button
    property string buttonText
    property alias backg: backg
    property alias texte: texte

    contentItem: Text {
        id: texte
        text: buttonText
        // color: button.down ? "black" : "white"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 14
        font.bold: false
        //font.letterSpacing: 2
    }

    background: Rectangle {
        id: backg
        implicitWidth: 86
        implicitHeight: 40
        radius: 6
        color: button.down ? Universal.foreground.lighter(
                                 1.1) : Universal.foreground
    }
}
