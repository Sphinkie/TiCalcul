import QtQuick
import QtQuick.Controls.Universal


/*! **********************************************************************************************************
 * \class Le type QML FieldInput gère un champ numérique de l'IHM.
 *        Il est associé à un objet C++ Afficheur dont il reçoit les valeurs à afficher.
 *        Il y a un FieldInput pour chaque unité: Secondes, Millisecondes, HMSI, etc.
 *************************************************************************************************************/
Item {
    property alias text: result.text
    property alias color: bg.color
    implicitWidth: 120
    implicitHeight: 40

    Rectangle {
        id: bg
        color: Universal.altMediumColor
        anchors.fill: parent

        Text {
            id: result
            text: "result"
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            leftPadding: 8
            font.pixelSize: 15
            font.family: "Courier"
            font.bold: true
            color: Universal.chromeAltLowColor
        }
    }
}
