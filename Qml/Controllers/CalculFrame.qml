import QtQuick
import TiCalcul
import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel central (zone des calculs).
 * ***************************************************************** */
CalculFrameForm {
    id: calculFrame
    property string msgText: "ready..."


    /* Messages:
            msgText: "fenetre: " + window.width + "x" + window.height
            msgText = "timecode addition"
            msgText = "timecode soustraction"
            msgText = "TC1 24'H complement"
            msgText = "ready"
            msgText = ""
    }
    */
    tc1.onClicked: {
        console.log("TC1 clicked ! ")
    }

    bRectifyTc1.onClicked: {
        tc1_aff_4.rectifyHMSI()
    }

    bFramerateTc1.onClicked: {
        if (tc1_aff_4.framerate === 25)
            tc1_aff_4.framerate = 50
        else
            tc1_aff_4.framerate = 25
    }

    tc2.onClicked: {
        console.log("TC2 clicked ! ")
    }

    bRectifyTc2.onClicked: {
        tc2_aff_4.rectifyHMSI()
    }

    bFramerateTc2.onClicked: {
        if (tc2_aff_4.framerate === 25)
            tc2_aff_4.framerate = 50
        else
            tc2_aff_4.framerate = 25
    }

    bSwap.onClicked: {
        console.log("Swap ! ")
        calculateur.swap()
    }

    bMem.onClicked: {
        console.log("Memory ! ")
        calculateur.memorize()
    }
}
