import QtQuick

import "../Vues"


/*! *****************************************************************
 *  Controlleur pour le panel de droite
 * ***************************************************************** */
RightFrameForm {

    btFramerate.onClicked: {
        console.log("TiButton btFramerate clicked ! ")
        operandeTC2.setFramerate(50)
    }

    btClear.onClicked: {
        console.log("TiButton btClear clicked ! ")
        operandeTC2.clear()
    }
}
