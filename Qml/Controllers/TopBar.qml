import QtQuick
import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype TopBar
  \inqmlmodule QTiCalcul
  \inherits TopBarForm
  \brief Controller pour la barre du haut, qui contient le bouton pour AboutPopup.
 */
TopBarForm {

    btAbout.onClicked: {
        console.log("about TiCalcul")
        aboutPopup.open()
    }
}
