import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Controllers"

Item {
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
            text: TC2aff_1.displayValue
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
            text: TC2aff_2.displayValue
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
            text: TC2aff_3.displayValue
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
            text: TC2aff_6.displayValue
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
            text: TC2aff_7.displayValue
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
            text: TC2aff_4.displayValue
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
            text: TC2aff_5.displayValue
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // ---------------------------------------
        TiButton {
            id: btFrameRate
            buttonText: "framerate"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        TiButton {
            id: btClear
            buttonText: "clear"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
