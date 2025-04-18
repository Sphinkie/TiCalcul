import QtQuick
import QtQuick.Controls.Universal

/* *********************************************************************************** */

/*!
  \qmltype KeyboardKeyForm
  \inqmlmodule QTiCalcul
  \brief fournit un bouton customisé pour les touches du clavier virtuel.
  
  Les clics sur les boutons sont gérés par le controleur parent \l Keyboard.
  \sa Keyboard
*/
Button {
    id: button
    property alias texte: texte
	
	/*! \qmlproperty string KeyboardKeyForm::buttonText */
    property string buttonText

    display: AbstractButton.TextOnly

    contentItem: Text {
        id: texte
        text: buttonText
		// Coumleur du texte. 
        color: parent.enabled ? Universal.chromeAltLowColor : Universal.chromeDisabledHighColor
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
