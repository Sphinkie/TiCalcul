import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal
import TiCalcul

import "../Components"
import "../Controllers"

Item {
    property alias btClear: btClear

    GridLayout {
        id: zoneSaisieRight
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 2

        FieldInput {
            // text: "SECONDS"
            afficheur: TC2_aff_1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "seconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "MILLISECONDS"
            afficheur: TC2_aff_2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "milliseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            // text: "MICROSECS"
            afficheur: TC2_aff_3
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "microseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "FRAMES"
            afficheur: TC2_aff_6
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (25fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "FRAMES"
            afficheur: TC2_aff_7
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (50fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------


        /*
        FieldInput {
            //text: "HH:MM:SS:II"
            afficheur: TC1_aff_4
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "HMSI (25fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
*/
        // ---------------------------------------
        FieldInput {
            //text: "DD + HH:MM:SS:II"
            afficheur: TC2_aff_5
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "HMS,ms"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        TiButton {
            id: btClear
            Layout.rightMargin: 4
            Layout.leftMargin: 0
            Layout.topMargin: 4
            buttonText: "clear"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        Item {
            id: emptySpace
        }
    }
}
