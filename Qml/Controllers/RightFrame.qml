import QtQuick

import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype RightFrame
  \inqmlmodule QTiCalcul
  \inherits RightFrameForm
  \brief Controlleur pour le panel de droite.
 */
RightFrameForm {

    btClear.onClicked: {
        console.debug("TiButton btClear TC2 clicked ! ")
        operandeTC2.clearValeurPivot()
        operandeRES.clearValeurPivot()
    }
}
