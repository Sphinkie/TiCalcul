import QtQuick
import TiCalcul
import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype CalculFrame
  \inqmlmodule QTiCalcul
  \inherits CalculFrameForm
  \brief  Controlleur pour le panel central (zone des calculs).
 */
CalculFrameForm {
    id: calculFrame


    /*! \qmlproperty string CalculFrame::msgText
        Petit message pouvant être affiché à coté du picto.
     */
    property string msgText: ""


    /* Messages:
            msgText: "fenetre: " + window.width + "x" + window.height
            msgText = "timecode addition"
            msgText = "timecode soustraction"
            msgText = "TC1 24'H complement"
            msgText = "ready"
            msgText = ""
    */
    tc1.onClicked: {
        console.debug("TC1 clicked ! ")
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
        console.debug("TC2 clicked ! ")
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
        console.debug("Swap ! ")
        calculateur.swap()
    }

    bMem.onClicked: {
        console.debug("Memory ! ")
        calculateur.memorize()
    }
}
