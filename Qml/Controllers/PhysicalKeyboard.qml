import QtQuick

// Gestion des touches du clavier
Item {

    Keys.onDigit1Pressed: event => afficheurActif.afficheur.addDigit("1")
    Keys.onDigit2Pressed: event => afficheurActif.afficheur.addDigit("2")
    Keys.onDigit3Pressed: event => afficheurActif.afficheur.addDigit("3")
    Keys.onDigit4Pressed: event => afficheurActif.afficheur.addDigit("4")
    Keys.onDigit5Pressed: event => afficheurActif.afficheur.addDigit("5")
    Keys.onDigit6Pressed: event => afficheurActif.afficheur.addDigit("6")
    Keys.onDigit7Pressed: event => afficheurActif.afficheur.addDigit("7")
    Keys.onDigit8Pressed: event => afficheurActif.afficheur.addDigit("8")
    Keys.onDigit9Pressed: event => afficheurActif.afficheur.addDigit("9")
    Keys.onDigit0Pressed: event => afficheurActif.afficheur.addDigit("0")

    // TODO : Mouvements
    Keys.onRightPressed: event => console.log("move Right")
    Keys.onDownPressed: event => console.log("move Down")
    Keys.onLeftPressed: event => console.log("move Left")
    Keys.onUpPressed: event => console.log("move Up")

    // Autres touches
    Keys.onDeletePressed: event => afficheurActif.afficheur.removeLastDigit()
    Keys.onPressed: event => {
                        if (event.key === Qt.Key_Plus) {
                            calculateur.add()
                            // Si on était sur TC1, on passe sur TC2.
                            afficheurActif.afficheur = afficheurActif.afficheur.partner
                        }

                        if (event.key === Qt.Key_Minus) {
                            calculateur.substract()
                            // Si on était sur TC1, on passe sur TC2.
                            afficheurActif.afficheur = afficheurActif.afficheur.partner
                        }
                        if (event.key === Qt.Key_Period) {
                            afficheurActif.afficheur.addDigit(".")
                        }
                        if (event.key === Qt.Key_Backspace) {
                            afficheurActif.afficheur.removeLastDigit()
                        }
                        event.accepted = true
                    }


    /*
    //  Testeur de touches:
    Keys.onPressed: event => {
                        console.log(event.key)
                        event.accepted = true
                    }
    */
}
