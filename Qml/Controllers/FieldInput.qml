import QtQuick
import TiCalcul

import "../Vues"


/* ********************************************************************************
 * \brief Mémorise l'afficheur actif, lors d'un click sur un afficheur FieldInput.
 * Si des touches clavier sont recues lorsque le bouton a le focus,
 * on les forwarde au gestionnaire de clavier.
 ***********************************************************************************/
FieldInputForm {
    id: control
    property bool bold: false

    Keys.forwardTo: [physicalKeyboard]

    onClicked: {
        afficheurActif.afficheur = afficheur
    }
}
