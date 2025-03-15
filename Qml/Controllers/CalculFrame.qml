import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel central (zone des calculs).
 * ***************************************************************** */
CalculFrameForm {

    tc1.onClicked: {
        console.log("TiButton  TC1 clicked ! ")
    }

    tc2.onClicked: {
        console.log("TiButton  TC2 clicked ! ")
    }

    // TODO : Gestion du bouton SWAP
}
