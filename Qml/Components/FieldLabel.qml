import QtQuick
import QtQuick.Controls.Universal


/*! ********************************************************************************
 * \brief Affiche un libellé à coté de chaque afficheur FieldInput.
 ***********************************************************************************/
Label {
    id: label
    text: "label"
    horizontalAlignment: Text.AlignRight
    verticalAlignment: Text.AlignVCenter
    leftPadding: 8
    rightPadding: 8
    font.pixelSize: 14
    font.bold: true
    color: Universal.baseMediumColor
}
