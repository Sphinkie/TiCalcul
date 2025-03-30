import QtQuick

import "../Vues"


/* ********************************************************************************
 * \brief : Petit bouton arrondi. Le clic est géré par le parent.
 * Si des touches clavier sont recues lorsque le bouton a le focus,
 * on les forwarde au gestionnaire de clavier.
 ***********************************************************************************/
TiButtonForm {
    id: control

    Keys.forwardTo: [physicalKeyboard]
}
