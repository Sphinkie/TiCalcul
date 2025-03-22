import QtQuick
import TiCalcul

import "../Vues"


/*! ********************************************************************************
 * \brief Mémorise l'afficheur actif, lors d'un click sur un afficheur FieldInput.
 ***********************************************************************************/
FieldInputForm {
	id: control
	property bool bold: false


    onClicked: {
        afficheurActif.afficheur = afficheur
    }
}
