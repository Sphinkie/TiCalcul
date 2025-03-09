import QtQuick
import TiCalcul

import "../Vues"


/*!
 * \brief Mémorise l'afficheur actif, lors d'un click sur un afficheur FieldInput.
 */
FieldInputForm {

    onClicked: {
        afficheurActif.name = afficheur
    }
}
