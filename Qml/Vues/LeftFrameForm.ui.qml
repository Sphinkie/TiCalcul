import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal
import TiCalcul

import "../Components"
import "../Controllers"

Item {
    property alias btClear: btClear

    GridLayout {
        id: zoneSaisie
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 2

        FieldLabel {
            text: "seconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "SECONDS"
            afficheur: TC1_aff_1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "milliseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "MILLISECONDS"
            afficheur: TC1_aff_2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "microseconds"
            //justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "MICROSECS"
            afficheur: TC1_aff_3
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (25fps)"
            //justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            afficheur: TC1_aff_6
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (50fps)"
            //justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            afficheur: TC1_aff_7
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "HMS,ms"
            //justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "DD + HH:MM:SS:mmm"
            // TODO: rendre non éditable
            afficheur: TC1_aff_5
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        Item {
            id: emptySpace
            // Layout.topMargin: 4
            // Layout.rightMargin: 4
            // Layout.leftMargin: 4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: btClear
            Layout.topMargin: 4
            Layout.rightMargin: 0
            Layout.leftMargin: 4
            buttonText: "clear"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
    }
}
