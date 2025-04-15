import QtQuick
import TiCalcul

import "../Vues"

/* ********************************************************************************************************** */


/*!
  \qmltype FieldInput
  \inqmlmodule QTiCalcul
  \brief Mémorise l'afficheur actif, lors d'un click sur un afficheur FieldInput.

   Si des touches clavier sont reçues lorsque le bouton a le focus,
   on les forwarde au gestionnaire de clavier.
 */
FieldInputForm {
    id: control
    property bool bold: false

    // Les touches du clavier sont forwardées vers le Gestionnaire
    Keys.forwardTo: [physicalKeyboard]

    // Un item cliqué devient l'afficheur actif
    onClicked: {
        afficheurActif.afficheur = afficheur
    }
}
