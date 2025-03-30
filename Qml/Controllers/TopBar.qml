import QtQuick
import "../Vues"


/*!
 * \brief Controller pour la barre du haut qui contient le bouton About.
 */
TopBarForm {

    btAbout.onClicked: {
        console.log("about TiCalcul")
        aboutPopup.open()
    }
}
