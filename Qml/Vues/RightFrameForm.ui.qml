import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal
import TiCalcul

import "../Components"
import "../Controllers"


/*! ***********************************************************************************
 * \brief Panneau de droite, avec l'affichage du Timecode TC2 dans différentes unités.
 **************************************************************************************/
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
            afficheur: tc2_aff_1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "seconds"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "MILLISECONDS"
            afficheur: tc2_aff_2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "milliseconds"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            // text: "MICROSECS"
            afficheur: tc2_aff_3
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "microseconds"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "FRAMES"
            afficheur: tc2_aff_6
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (25fps)"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "FRAMES"
            afficheur: tc2_aff_7
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (50fps)"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "DD + HH:MM:SS:II"
            enabled: false
            afficheur: tc2_aff_5
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "HMS,ms"
            horizontalAlignment: Text.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        TiButton {
            id: btClear
            Layout.rightMargin: 0
            Layout.leftMargin: 0
            Layout.topMargin: 6
            buttonText: "clear"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        Item {
            id: emptySpace
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
    }
}
