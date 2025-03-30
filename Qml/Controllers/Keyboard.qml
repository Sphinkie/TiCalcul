import QtQuick
import "../Vues"


/* **************************************************************************
 * Le Keyboard est composé d'un ensemble de boutons KeyboardKey.
 * Le controleur détermine l'action déclenchée par chaque bouton, en
 * appelant une méthode C++ de l'afficheur actif.
 * Si des touches clavier sont recues lorsque le bouton a le focus,
 * on les forwarde au gestionnaire de clavier.
 ***************************************************************************** */
KeyboardForm {

    Keys.forwardTo: [physicalKeyboard]

    key0.onClicked: afficheurActif.afficheur.addDigit("0")
    key1.onClicked: afficheurActif.afficheur.addDigit("1")
    key2.onClicked: afficheurActif.afficheur.addDigit("2")
    key3.onClicked: afficheurActif.afficheur.addDigit("3")
    key4.onClicked: afficheurActif.afficheur.addDigit("4")
    key5.onClicked: afficheurActif.afficheur.addDigit("5")
    key6.onClicked: afficheurActif.afficheur.addDigit("6")
    key7.onClicked: afficheurActif.afficheur.addDigit("7")
    key8.onClicked: afficheurActif.afficheur.addDigit("8")
    key9.onClicked: afficheurActif.afficheur.addDigit("9")
    key00.onClicked: afficheurActif.afficheur.addDigit("00")
    keyDot.onClicked: afficheurActif.afficheur.addDigit(".")
    keyDel.onClicked: afficheurActif.afficheur.removeLastDigit()

    keyPlus.onClicked: calculateur.add()
    keyMinus.onClicked: calculateur.substract()
    keyComplt.onClicked: calculateur.complement()

    keyDot.enabled: {
        if (afficheurActif.afficheur.unit !== "SECONDS")
            return false
        else if (afficheurActif.afficheur.displayValue.includes('.'))
            return false
        else
            return true
    }
}
