import QtQuick

/* ********************************************************************************************************** */


/*!
  \qmltype PhysicalKeyboard
  \inqmlmodule QTiCalcul
  \brief Gestion des touches du clavier.

  Les touches gérées sont les touches du pavé numérique (\c 0 à \c 9),
  les flèches pour se déplacer entre des afficheurs d'un même opérande,
  \c Tab pour passer d'un opérateur à l'autre,
  \c Plus et \c Moins pour les opérations.

  On gère aussi le \c point, \c delete, \c Ctrl-C et \c Ctrl-V.

  La touche \c k (spy) pour voir le contenu du tampon.
 */
Item {

  // Chiffres
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

  // Mouvements
  Keys.onRightPressed: event => afficheurActif.afficheur = afficheurActif.afficheur.right
  Keys.onDownPressed: event => afficheurActif.afficheur = afficheurActif.afficheur.down
  Keys.onLeftPressed: event => afficheurActif.afficheur = afficheurActif.afficheur.left
  Keys.onUpPressed: event => afficheurActif.afficheur = afficheurActif.afficheur.up
  Keys.onTabPressed: event => afficheurActif.afficheur = afficheurActif.afficheur.partner

  // SUPPR : clear
  Keys.onDeletePressed: event => afficheurActif.afficheur.parent.clearValeurPivot()

  // Autres touches
  Keys.onPressed: event => {

                    if (event.key === Qt.Key_K) // spy
                    {
                      console.log(tampon.text)
                      event.accepted = true
                    }
                    // CTRL-C : copy
                    if ((event.key === Qt.Key_C)
                        && (event.modifiers & Qt.ControlModifier)) {
                      // on copie de Afficheur vers le tampon
                      tampon.text = afficheurActif.afficheur.copy()
                      // puis du tampon vers le clipboard Windows
                      tampon.selectAll()
                      tampon.copy()
                      console.log("Ctrl+C")
                      event.accepted = true
                    }
                    // CTRL-V : paste
                    if ((event.key === Qt.Key_V)
                        && (event.modifiers & Qt.ControlModifier)) {
                      // on copie du clipboard vers le tampon
                      tampon.clear()
                      tampon.paste()
                      // puis du tampon vers l'afficheur
                      afficheurActif.afficheur.paste(tampon.text)
                      console.log("Ctrl+V")
                      event.accepted = true
                    }
                    // + : addition
                    if (event.key === Qt.Key_Plus) {
                      calculateur.add()
                      // Si on était sur TC1, on passe sur TC2.
                      afficheurActif.afficheur = afficheurActif.afficheur.partner
                      event.accepted = true
                    }
                    // - : soustraction
                    if (event.key === Qt.Key_Minus) {
                      calculateur.substract()
                      // Si on était sur TC1, on passe sur TC2.
                      afficheurActif.afficheur = afficheurActif.afficheur.partner
                      event.accepted = true
                    }
                    // . : point
                    if (event.key === Qt.Key_Period) {
                      afficheurActif.afficheur.addDigit(".")
                      event.accepted = true
                    }
                    // <- : del
                    if (event.key === Qt.Key_Backspace) {
                      afficheurActif.afficheur.removeLastDigit()
                      event.accepted = true
                    }
                  }


  /*
    //  Testeur de touches:
    Keys.onPressed: event => {
                        console.log(event.key)
                        event.accepted = true
                    }
    */

  // Zone tampon vers le clipboard
  TextEdit {
    id: tampon
    visible: false
  }
}
