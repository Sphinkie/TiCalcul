import QtQuick

import "../Vues"


/*! *****************************************************************
 * \brief Controlleur pour le panel de droite.
 * ***************************************************************** */
RightFrameForm {

    btClear.onClicked: {
        operandeTC2.clear()
    }
}
