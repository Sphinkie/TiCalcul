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

        FieldInput {
            // text: "SECONDS"
            text: aff_1.value
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "seconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            //text: "MILLISECONDS"
            text: aff_2.value
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "milliseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            // text: "MICROSECS"
            text: aff_3.value
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "microseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "FRAMES"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (25fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "FRAMES"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "frames (50fps)"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "HH:MM:SS:II"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "HMSI"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "DD + HH:MM:SS:II"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "day + HMSI"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        TiButton {
            id: btClear
            buttonText: "Clear"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
