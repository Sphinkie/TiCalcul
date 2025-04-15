import QtQuick

import "../Vues"

/* ********************************************************************************************************** */
/* ********************************************************************************************************** */

/*!
  \qmltype LeftFrame
  \inqmlmodule QTiCalcul
  \inherits LeftFrameForm
  \brief Controlleur pour le panel de gauche.
 */
LeftFrameForm {

    // Clic sur le bouton CLEAR TC1
    btClear.onClicked: {
        console.debug("Button btClear TC1 clicked ! ")
        operandeTC1.clearValeurPivot()
        operandeRES.clearValeurPivot()
        calculateur.clear()
    }
}
