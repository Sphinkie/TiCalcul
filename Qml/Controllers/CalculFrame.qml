import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel central (zone des calculs).
 * ***************************************************************** */
CalculFrameForm {

    tc1.onClicked: {
        console.log("TiButton TC1 clicked ! ")
    }

    bFramerateTc1.onClicked: {
        console.log("Framerate TC1 clicked ! ")
        if (tc1_aff_4.framerate === 25)
            tc1_aff_4.framerate = 50
        else
            tc1_aff_4.framerate = 25
    }

    tc2.onClicked: {
        console.log("TiButton TC2 clicked ! ")
    }

    bFramerateTc2.onClicked: {
        console.log("Framerate TC2 clicked ! ")
        if (tc2_aff_4.framerate === 25)
            tc2_aff_4.framerate = 50
        else
            tc2_aff_4.framerate = 25
    }

    // TODO : Gestion du bouton SWAP
}
