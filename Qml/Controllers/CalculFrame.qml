import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel central (zone des calculs).
 * ***************************************************************** */
CalculFrameForm {

    tc1.onClicked: {
        console.log("TiButton btFramerate TC1 clicked ! ")
    }

    tc2.onClicked: {
        console.log("TiButton btFramerate TC2 clicked ! ")
    }

    // TODO : Ajouter un bouton SWAP au nivea de la deuxième ligne
}
