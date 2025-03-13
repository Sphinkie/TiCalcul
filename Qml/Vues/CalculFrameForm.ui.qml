import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"
import "../Controllers"

Item {
    //    id: _item
    property alias tc1: tc1
    property alias tc2: tc2

    GridLayout {
        id: zoneResults
        anchors.fill: parent
        Layout.margins: 24
        columnSpacing: 0
        rowSpacing: 0
        columns: 3

        // ------------------------------------------------------------
        // 1ere ligne
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
            //text: "..:..:..:.."
            afficheur: TC1_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc1
            buttonText: "25fps"
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
        // 2eme ligne
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
            // text: "..:..:..:.."
            afficheur: TC2_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc2
            buttonText: "25fps"
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
            afficheur: RESULT_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        // ------------------------------------------------------------
        // Zone vide en bas
        // ------------------------------------------------------------
        Item {
            Layout.preferredHeight: 85
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.rowSpan: 1
            Layout.columnSpan: 3
            Layout.row: 7
        }
    }
}
