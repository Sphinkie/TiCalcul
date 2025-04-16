import QtQuick
import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype TopBar
  \inqmlmodule QTiCalcul
  \inherits TopBarForm
  \brief Controleur pour la barre du haut, qui contient le bouton pour AboutPopup.
 */
TopBarForm {

  btAbout.onClicked: {
    console.log("open About TiCalcul")
    aboutPopup.open()
  }
}
