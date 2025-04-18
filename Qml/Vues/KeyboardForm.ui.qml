import QtQuick
import QtQuick.Layouts


/* *********************************************************************************** */

/*!
  \qmltype KeyboardForm
  \inqmlmodule QTiCalcul
  \brief Le KeyboardForm est un ensemble de 18 boutons de type KeyboardKeyForm.
  
  Cette Form est attachée à un controleur \l Keyboard qui gère les actions suite à un appui sur un bouton.
  \sa Keyboard, KeyboardKeyForm
*/
GridLayout {
    property alias key0: key0
    property alias key1: key1
    property alias key2: key2
    property alias key3: key3
    property alias key4: key4
    property alias key5: key5
    property alias key6: key6
    property alias key7: key7
    property alias key8: key8
    property alias key9: key9
    property alias key00: key00
    property alias keyDot: keyDot
    property alias keyDel: keyDel
    property alias keyPlus: keyPlus
    property alias keyMinus: keyMinus
    property alias keyComplt: keyComplt

    id: keyboardGrid
    columns: 4

    KeyboardKeyForm {
        id: key1
        buttonText: "1"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key2
        buttonText: "2"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key3
        buttonText: "3"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: keyPlus
        buttonText: "+"
        texte.font.pointSize: 28
        enabled: tc1_aff_1.displayValue ? true : false
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key4
        buttonText: "4"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key5
        buttonText: "5"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key6
        buttonText: "6"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: keyMinus
        buttonText: "-"
        texte.font.pointSize: 28
        enabled: tc1_aff_1.displayValue ? true : false
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key7
        buttonText: "7"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key8
        buttonText: "8"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key9
        buttonText: "9"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: keyComplt
        buttonText: "24'C"
        enabled: tc1_aff_1.displayValue ? true : false
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key00
        buttonText: "00"
        enabled: (afficheurActif.afficheur.unit === "HMSI"
                  || afficheurActif.afficheur.unit === "MICROSECONDS"
                  || afficheurActif.afficheur.unit === "MILLISECONDS") ? true : false
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: key0
        buttonText: "0"
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: keyDot
        buttonText: "."
        // enabled: est défini dans le controller
        // enabled: (afficheurActif.afficheur.unit === "SECONDS") || (tc1_aff_1.displayValue.contains('.')) ? true : false
        Layout.fillWidth: true
    }
    KeyboardKeyForm {
        id: keyDel
        buttonText: "\u232b"
        texte.font.pointSize: 28
        Layout.fillWidth: true
    }
}
