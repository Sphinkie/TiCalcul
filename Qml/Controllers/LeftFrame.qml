import QtQuick

import "../Vues"


/* *****************************************************************
 * \brief Controlleur pour le panel de gauche.
 * ***************************************************************** */
LeftFrameForm {

    // Clic sur le bouton CLEAR TC1
    btClear.onClicked: {
        console.log("Button btClear TC1 clicked ! ")
        operandeTC1.clearValeurPivot()
        operandeRES.clearValeurPivot()
        calculateur.clear()
    }
}
