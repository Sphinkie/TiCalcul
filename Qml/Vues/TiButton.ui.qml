import QtQuick
import QtQuick.Controls.Universal

/*!
 * Le type TiButton offre des bouttons customisés au niveau des couleurs, arrondi, et police.
 */
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
        font.pointSize: 15
        font.bold: false
        //font.letterSpacing: 2
    }

    background: Rectangle {
        id: backg
        implicitWidth: 86
        implicitHeight: 40
        color: button.down ? Universal.foreground.lighter(1.1) : Universal.foreground
        radius: 6		
    }
	
}
