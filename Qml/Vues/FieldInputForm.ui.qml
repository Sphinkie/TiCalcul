import QtQuick
import QtQuick.Controls.Universal
import TiCalcul


/* *************************************************************************
 * Le FieldInputForm est associé à un objet C++ Afficheur.
 * Il affiche une valeur (string) qui est une propriété partagée de l'objet.
 * Il hérite d'un Button car un click permet de le sélectionner.
 * Cette Form est associée à un controlleur FieldInput.
 **************************************************************************** */
Button {
    //! Cet afficheur doit être fourni par le parent lors de la création du FieldInput.
    required property Afficheur afficheur
    property alias displaytext: btText.text

    // Le texte affiché est la String envoyée par l'afficheur
    contentItem: Text {
        id: btText
        text: afficheur.displayValue ? afficheur.displayValue : afficheur.hint
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        font.family: "Courier"
        font.bold: control.bold
        // text color
        color: afficheur.correct ? (afficheur.displayValue ? Universal.chromeAltLowColor // Couleur normale
                                                           : Universal.chromeHighColor.darker(
                                                                 1.2)) // couleur des hints
                                 : Universal.accent // couleur si incorrect
    }

    // La couleur de fond est blanche quand l'afficheur est sélectioné
    background: Rectangle {
        id: btBackground
        implicitWidth: 160
        implicitHeight: 40
        // color: parent.pressed ? "white" : "green"
        // color: parent.enabled ? "teal" : "green"
        color: parent.enabled ? ((afficheurActif.afficheur
                                  === afficheur) ? Universal.altHighColor // si focus => blanc
                                                 : Universal.altMediumHighColor) // si non-focus : vert pale
                              : Universal.altMediumColor // si disable : vert moyen
        border.color: Universal.baseLowColor
        border.width: (afficheurActif.afficheur === afficheur) ? 2 : 0
    }
}
