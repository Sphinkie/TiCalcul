import QtQuick
import TiCalcul
import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel central (zone des calculs).
 * ***************************************************************** */
CalculFrameForm {
    id: calculFrame
    //msgText: "fenetre: " + window.width + "x" + window.height
    property string msgText: "ready..."

    // onOperatChanged: console.log("hop !")

    // calculateur.onOperationChanged: {console.log("onOperationChanged: evalutating operateur.text")    }
    onOperateurChanged: {
        console.log("evalutating operateur.text")
        if (calculateur.operation === calculateur.addition) {
            console.log("timecode addition")
            msgText = "timecode addition"
            operateur.text = "+"
        } else if (calculateur.operation === calculateur.soustraction) {
            console.log("timecode soustraction")
            msgText = "timecode soustraction"
            operateur.text = "-"
        } else if (calculateur.operation === calculateur.complt)
            operateur.text = "Cmplt"
        else
            operateur.text = ""
    }

    operateur.text: calculateur.operat

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
