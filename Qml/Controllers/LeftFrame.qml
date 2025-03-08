import QtQuick

import "../Vues"


/*! *****************************************************************
 *  Controlleur pour le panel de gauche
 * ***************************************************************** */
LeftFrameForm {

    btFramerate.onClicked: {
        console.log("TiButton btFramerate clicked ! ")
        TC1_aff_4.setFrameRate(50) // afficheur HMSI
    }

    btClear.onClicked: {
        console.log("TiButton btClear clicked ! ")
        operandeTC1.clear()
    }
}
