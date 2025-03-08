import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"

Item {
    property alias btClear: btClear
    property alias btFramerate: btFramerate

    GridLayout {
        id: zoneSaisie
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 2

        FieldInput {
            // text: "SECONDS"
            fieldText: TC1_aff_1.displayValue
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
            fieldText: TC1_aff_2.displayValue
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
            fieldText: TC1_aff_3.displayValue
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
            fieldText: TC1_aff_6.displayValue
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
            fieldText: TC1_aff_7.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (50fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "HH:MM:SS:II"
            fieldText: TC1_aff_4.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "HMSI (25fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldInput {
            //text: "DD + HH:MM:SS:II"
            fieldText: TC1_aff_5.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "day + HMSm"
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
        TiButton {
            id: btFramerate
            Layout.rightMargin: 4
            Layout.leftMargin: 4
            Layout.topMargin: 4
            buttonText: "framerate"
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
    }
}
