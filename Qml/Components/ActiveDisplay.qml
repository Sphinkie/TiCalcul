import QtQuick
import TiCalcul

/* ********************************************************************************************************** */


/*!
  \qmltype ActiveDisplay
  \inqmlmodule QTiCalcul
  \brief Mémorise l'afficheur actif.

   Il est commun pour TC1 et TC2, car un seul display est éditable à la fois.

   L'afficheur actif va recevoir les touches cliquées du clavier.
   Au niveau apparence, l'afficheur actif a une couleur de background plus claire que les autres.
   On change d'afficheur actif en cliquant sur un autre afficheur (cad un autre FieldInput).
 */
Item {
    /*! \qmlproperty Afficheur ActiveDisplay::afficheur */
    property Afficheur afficheur

    onAfficheurChanged: {
        // On envoie un signal à tous les afficheurs pour dire lequel est actif
        activeDisplay(afficheur.objectName)
    }

    // Initialisation
    Component.onCompleted: {
        console.log("Initialisation de l'afficheur actif")
        afficheurActif.afficheur = tc1_aff_4
    }
}
