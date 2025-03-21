import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel de droite.
 * ***************************************************************** */
RightFrameForm {

    btClear.onClicked: {
        console.log("TiButton btClear TC2 clicked ! ")
        operandeTC2.clearValeurPivot()
        operandeRES.clearValeurPivot()
    }
}
