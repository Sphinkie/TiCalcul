import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 2.15
import "../Controllers"

Item {
    id: _item
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        GridLayout {
            id: zoneSaisie
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 24
            columns: 2
            rows: 4
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
                text: "FRAMES"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldLabel {
                text: "frames (25 fps)"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        RowLayout {
            id: zoneOperandes
            Layout.fillWidth: true
            Layout.rightMargin: 24
            Layout.leftMargin: 24
            spacing: 24
            height: btCopyToTc1.height
            TiButton {
                id: btCopyToTc1
                text: "Copy to TC1"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TiButton {
                id: btCopyToTc2
                text: "Copy to TC2"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TiButton {
                id: btClear
                text: "Clear"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        GridLayout {
            id: zoneResults
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 24
            columns: 3
            rows: 3

            FieldResult {
                text: "TC1"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldResult {
                id: tc1
                text: "..:..:..:.."
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TiButton {
                id: btSwap
                text: "v^"
                Layout.rowSpan: 2
                Layout.columnSpan: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldResult {
                text: "TC2"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldResult {
                id: tc2
                text: "..:..:..:.."
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldResult {
                text: "RESULT"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            FieldResult {
                id: result
                text: "..:..:..:.."
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
