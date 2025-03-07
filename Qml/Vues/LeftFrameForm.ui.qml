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
            text: TC1aff_1.displayValue
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
            text: TC1aff_2.displayValue
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
            text: TC1aff_3.displayValue
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
            text: TC1aff_6.displayValue
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
            text: TC1aff_7.displayValue
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
            text: TC1aff_4.displayValue
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
            text: TC1aff_5.displayValue
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
            buttonText: "clear"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        TiButton {
            id: btFramerate
            buttonText: "framerate"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
