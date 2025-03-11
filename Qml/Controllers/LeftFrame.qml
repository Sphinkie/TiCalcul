import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel de gauche.
 * ***************************************************************** */
LeftFrameForm {

    btFramerate.onClicked: {
        console.log("TiButton btFramerate clicked ! ")
        TC1_aff_4.setFrameRate(50) // Afficheur HMSI
    }

    btClear.onClicked: {
        console.log("TiButton btClear clicked ! ")
        operandeTC1.clear()
    }
}
