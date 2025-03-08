import QtQuick

import "../Vues"


/*! *****************************************************************
 *  Controlleur pour le panel de gauche
 * ***************************************************************** */
LeftFrameForm {

    btFramerate.onClicked: {
        console.log("TiButton btFramerate clicked ! ")
        operandeTC1.setFramerate(50)
    }

    btClear.onClicked: {
        console.log("TiButton btClear clicked ! ")
        operandeTC1.clear()
    }
}
