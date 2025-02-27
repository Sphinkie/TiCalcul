import QtQuick
import QtQuick.Layouts 2.15
import "../Controllers"

Item {
    id: _item
    GridLayout {
        id: zoneResults
        anchors.fill: parent
        Layout.margins: 24
        columnSpacing: 0
        rowSpacing: 0
        columns: 2

        // ------------------------------------------------------------
        // 1ere ligne
        // ------------------------------------------------------------
        FieldResult {
            id: lbTc1
            text: "TC1"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldResult {
            id: tc1
            text: "..:..:..:.."
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        /*TiButton {
            id: btSwap
            buttonText: "v^"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rowSpan: 2
            Layout.columnSpan: 1
        }*/
        // ------------------------------------------------------------
        // Operande
        // ------------------------------------------------------------
        FieldResult {
            id: lbOperande
            text: "+"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rowSpan: 1
            Layout.columnSpan: 2
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
        FieldResult {
            id: tc2
            text: "..:..:..:.."
            Layout.fillHeight: true
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
