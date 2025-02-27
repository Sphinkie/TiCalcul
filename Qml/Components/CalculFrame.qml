import QtQuick
//import QtQuick.Controls.Universal
import QtQuick.Layouts 2.15
import "../Controllers"

Item {
    id: _item
    // background: Universal.background
    GridLayout {
        id: zoneResults
        anchors.fill: parent
        Layout.margins: 24
        columns: 3
        rows: 3

        FieldResult {
            id: lbTc1
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
            id: lbTc2
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
        RowLayout {
            id: zoneOperandes
            Layout.fillWidth: true
            Layout.rightMargin: 24
            Layout.leftMargin: 24
            spacing: 24
            height: 40 // btCopyToTc1.height
            Layout.rowSpan: 1
            Layout.columnSpan: 3

            TiButton {
                id: btCopyToTc1
                text: "Add"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TiButton {
                id: btCopyToTc2
                text: "Sub"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TiButton {
                id: btClear
                text: "24'C"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
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
