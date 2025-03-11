import QtQuick
import "../Vues"

KeyboardForm {

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

    keyPlus.onClicked: console.log(afficheurActif.afficheur.getName())
    keyMinus.onClicked: console.log("KeyboardKey - clicked !")
    keyComplt.onClicked: console.log("KeyboardKey Complt clicked !")
}
