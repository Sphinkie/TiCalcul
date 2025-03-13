import QtQuick
import QtQuick.Controls.Universal
import TiCalcul


/*! *****************************************************************
 * Le FieldInputForm est associé à un objet C++ Afficheur.
 * Il affiche une valeur (string) qui est une propriété partagée de l'objet.
 * Il hérite d'un Button car un click permet de le sélectionner.
 * Cette Form est associée à un controlleur FieldInput.
 ******************************************************************** */
Button {
    //! Cet afficheur doit être fourni par le parent lors de la création du Field input.
    required property Afficheur afficheur

    //! Le texte affiché est la String envoyée par l'afficheur
    contentItem: Text {
        text: afficheur.displayValue
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        // rightPadding: 8 // utile ?
        font.pixelSize: 15
        font.family: "Courier"
        font.bold: false
        color: Universal.chromeAltLowColor
    }

    //! La couleur de fond est blanche quand l'afficheur est sélectioné
    background: Rectangle {
        implicitWidth: 160
        implicitHeight: 40
        //color: parent.pressed ? "white" : "#c8e6ca"
        color: (afficheurActif.afficheur
                === afficheur) ? Universal.altHighColor : Universal.altMediumHighColor
    }
}
