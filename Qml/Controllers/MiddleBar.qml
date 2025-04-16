import QtQuick
import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype MiddleBar
  \inqmlmodule QTiCalcul
  \inherits MiddleBarForm
  \brief Controleur pour le bouton qui affiche ou masque le clavier \l Keyboard.
 */
MiddleBarForm {

  btHideKb.onClicked: {
    // On mémorise la taille précédente de la fenêtre
    var previousheight = window.height
    console.debug("taille précedente:", previousheight)

    // On masque le clavier
    if (keyboard.visible) {
      console.debug("hide keyboard")
      keyboard.visible = false
      // on redimentionne la fenêtre (et sa borne Min)
      window.minimumHeight = window.minimumHeight - keyboard.height
      window.height = previousheight - keyboard.height
      console.debug("nouvelle taille:", window.height)
    }
    // On affiche le clavier
    else {
      console.debug("show keyboard")
      keyboard.visible = true
      // on redimentionne la fenêtre (et sa borne Min)
      window.height = previousheight + keyboard.height
      window.minimumHeight = window.minimumHeight + keyboard.height
      console.debug("nouvelle taille:", window.height)
    }
  }
}
