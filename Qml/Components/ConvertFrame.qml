import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Controllers"

Item {
    GridLayout {
        id: zoneSaisie
        anchors.fill: parent
        Layout.leftMargin: 24
        Layout.rightMargin: 24
        columns: 2

        FieldInput {
            text: "SECONDS"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "seconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "MILLISECONDS"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldLabel {
            text: "milliseconds"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        FieldInput {
            text: "MICROSECS"
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
    }
}
