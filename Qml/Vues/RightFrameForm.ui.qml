import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal
import TiCalcul

import "../Components"
import "../Controllers"

Item {
    property alias btClear: btClear
    property alias btFramerate: btFramerate

    GridLayout {
        id: zoneSaisie
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 2

        FieldLabel {
            text: "seconds"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "SECONDS"
            fieldText: TC2_aff_1.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "milliseconds"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "MILLISECONDS"
            fieldText: TC2_aff_2.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "microseconds"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "MICROSECS"
            fieldText: TC2_aff_3.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (25fps)"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            fieldText: TC2_aff_6.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "frames (50fps)"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "FRAMES"
            fieldText: TC2_aff_7.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "HMSI (25fps)"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "HH:MM:SS:II"
            fieldText: TC2_aff_4.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        FieldLabel {
            text: "day + HMSm"
            justify: Text.AlignRight
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "DD + HH:MM:SS:II"
            fieldText: TC2_aff_5.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        TiButton {
            id: btFramerate
            Layout.topMargin: 4
            Layout.rightMargin: 4
            Layout.leftMargin: 4
            buttonText: "framerate"
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
