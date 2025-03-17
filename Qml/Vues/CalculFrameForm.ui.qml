import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"
import "../Controllers"

Item {
    property alias tc1: tc1
    property alias tc2: tc2
    property alias bFramerateTc1: bFramerateTc1
    property alias bFramerateTc2: bFramerateTc2

    GridLayout {
        id: zoneResults
        anchors.fill: parent
        Layout.margins: 24
        columnSpacing: 0
        rowSpacing: 0
        columns: 3

        // ------------------------------------------------------------
        // 1ere ligne - TC1 en HMSI
        // ------------------------------------------------------------
        FieldResult {
            id: labelTC1
            text: "TC1"
            color: Universal.altMediumHighColor
            Layout.preferredWidth: 80
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: tc1
            afficheur: tc1_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc1
            buttonText: tc1_aff_4.framerate + "fps"
            Layout.fillHeight: false
            Layout.fillWidth: false
        }

        // ------------------------------------------------------------
        // Operande
        // ------------------------------------------------------------
        FieldResult {
            id: lbOperande
            text: "+"
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.rowSpan: 1
            Layout.columnSpan: 3
        }
        // TODO : ajouter un bouton swap

        // ------------------------------------------------------------
        // 2eme ligne - TC2 en HMSI
        // ------------------------------------------------------------
        FieldResult {
            id: labelTC2
            text: "TC2"
            Layout.preferredWidth: 80
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: tc2
            afficheur: tc2_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc2
            buttonText: tc2_aff_4.framerate + "fps"
            Layout.fillHeight: false
            Layout.fillWidth: false
        }

        // ------------------------------------------------------------
        // Résultat
        // ------------------------------------------------------------
        FieldResult {
            text: "RESULT"
            Layout.preferredWidth: 80
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: result
            text: "..:..:..:.."
            afficheur: result_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        // ------------------------------------------------------------
        // Zone vide en bas
        // ------------------------------------------------------------
        Item {
            id: emptySpace
            Layout.preferredHeight: 85
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.rowSpan: 1
            Layout.columnSpan: 3
            Layout.row: 7
        }
    }
}
