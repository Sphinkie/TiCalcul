import QtQuick
import TiCalcul


/*! ***************************************************************************
  * Ce type (singleton) mémorise l'afficheur actif.
  * Il est commun pour TC1 et TC2, car un seul display est éditable à la fois.
  * L'afficheur actif va recevoir les touches cliquées du clavier.
  * Au niveau apparence, il a une couleur de background plus claire que les autres.
  * On change d'afficheur actif en cliquant sur un afficheur (cad un FieldInput).
  * *************************************************************************** */
Item {
    property Afficheur afficheur
    property string unit

    onAfficheurChanged: {
        unit: afficheur.getUnit()
        // On envoie un signal à tous les afficheurs pour dire lequel est actif
        activeDisplay(afficheur.objectName)
    }

    Component.onCompleted: {
        console.log("Initialisation de l'afficheur actif")
        afficheurActif.afficheur = tc1_aff_4
    }
}
