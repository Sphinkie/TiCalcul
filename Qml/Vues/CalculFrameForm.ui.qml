import QtQuick
import QtQuick.Layouts
import "../Components"
import "../Controllers"

Item {
    id: _item
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
            id: lbTc1
            width: 0
            text: "TC1"
            Layout.fillHeight: false
            Layout.fillWidth: true
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
            Layout.fillWidth: true
        }

        // ------------------------------------------------------------
        // Operande
        // ------------------------------------------------------------
        FieldResult {
            id: lbOperande
            text: "+"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rowSpan: 1
            Layout.columnSpan: 3
        }

        // ------------------------------------------------------------
        // 2eme ligne
        // ------------------------------------------------------------
        FieldResult {
            id: lbTc2
            text: "TC2"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            id: tc2
            // text: "..:..:..:.."
            afficheur: TC2_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        TiButton {
            id: bFramerateTc2
            buttonText: "25fps"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }

        // ------------------------------------------------------------
        // Résultat
        // ------------------------------------------------------------
        FieldResult {
            text: "RESULT"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldResult {
            id: result
            text: "..:..:..:.."
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
