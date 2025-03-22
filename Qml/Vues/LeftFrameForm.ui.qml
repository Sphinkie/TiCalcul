import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal
import TiCalcul

import "../Components"
import "../Controllers"


/*! ***********************************************************************************
 * \brief Panneau de gauche, avec l'affichage du Timecode TC1 dans différentes unités.
 **************************************************************************************/
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
            afficheur: tc1_aff_1
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
            afficheur: tc1_aff_2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "microseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "MICROSECS"
            afficheur: tc1_aff_3
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (25fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            afficheur: tc1_aff_6
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (50fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            afficheur: tc1_aff_7
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "HMS,ms"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "DD + HH:MM:SS:mmm"
            enabled: false
            afficheur: tc1_aff_5
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        Item {
            id: emptySpace
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: btClear
            Layout.topMargin: 6
            Layout.rightMargin: 0
            Layout.leftMargin: 0
            buttonText: "clear"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
    }
}
