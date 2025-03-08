import QtQuick

import "../Vues"


/*! *****************************************************************
 *  Controlleur pour le panel de droite
 * ***************************************************************** */
RightFrameForm {

    btFramerate.onClicked: {
        console.log("TiButton btFramerate clicked ! ")
        TC2_aff_4.setFrameRate(50) // afficheur HMSI
    }

    btClear.onClicked: {
        console.log("TiButton btClear clicked ! ")
        operandeTC2.clear()
    }
}
