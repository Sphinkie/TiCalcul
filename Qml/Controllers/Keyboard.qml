import QtQuick
import "../Vues"

KeyboardForm {

    key0.onClicked: afficheurActif.name.addDigit("0")
    key1.onClicked: afficheurActif.name.addDigit("1")
    key2.onClicked: afficheurActif.name.addDigit("2")
    key3.onClicked: afficheurActif.name.addDigit("3")
    key4.onClicked: afficheurActif.name.addDigit("4")
    key5.onClicked: afficheurActif.name.addDigit("5")
    key6.onClicked: afficheurActif.name.addDigit("6")
    key7.onClicked: afficheurActif.name.addDigit("7")
    key8.onClicked: afficheurActif.name.addDigit("8")
    key9.onClicked: afficheurActif.name.addDigit("9")
    key00.onClicked: afficheurActif.name.addDigit("00")
    keyDot.onClicked: afficheurActif.name.addDigit(".")
    keyDel.onClicked: afficheurActif.name.removeLastDigit()

    keyPlus.onClicked: console.log("KeyboardKey + clicked !")
    keyMinus.onClicked: console.log("KeyboardKey - clicked !")
    keyComplt.onClicked: console.log("KeyboardKey Complt clicked !")
}
