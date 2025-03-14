import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel de gauche.
 * ***************************************************************** */
LeftFrameForm {

    btClear.onClicked: {
        console.log("TiButton btClear TC1 clicked ! ")
        operandeTC1.clearValeurPivot()
    }
}
