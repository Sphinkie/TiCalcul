import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"
import "../Controllers"

Item {
    property alias tc1: tc1
    property alias tc2: tc2
    property alias bSwap: bSwap
    property alias bFramerateTc1: bFramerateTc1
    property alias bFramerateTc2: bFramerateTc2
    property alias bRectifyTc1: bRectifyTc1
    property alias bRectifyTc2: bRectifyTc2

    GridLayout {
        id: zoneResults
        anchors.fill: parent
        //Layout.margins: 24
        columnSpacing: 0
        rowSpacing: 0
        columns: 4

        // ------------------------------------------------------------
        // 1ere ligne - TC1 en HMSI
        // ------------------------------------------------------------
        FieldResult {
            id: labelTC1
            text: "TC1"
            color: Universal.altMediumHighColor
            Layout.preferredWidth: 52
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        SquareButton {
            id: bRectifyTc1
            text: "\u27f3"
            color: Universal.altMediumHighColor
            font.pixelSize: 24
            width: 32
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: tc1
            afficheur: tc1_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc1
            buttonText: tc1_aff_4.framerate + "fps"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 8
            backg.implicitHeight: 32
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // Operande
        // ------------------------------------------------------------
        FieldResult {
            id: lbOperande
            text: "+"
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.rowSpan: 1
            Layout.columnSpan: 3
        }
        TiButton {
            id: bSwap
            buttonText: "⇵"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 8
            backg.implicitHeight: 32
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // 2eme ligne - TC2 en HMSI
        // ------------------------------------------------------------
        FieldResult {
            id: labelTC2
            text: "TC2"
            Layout.preferredWidth: 52
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        SquareButton {
            id: bRectifyTc2
            text: "\u27f3"
            color: Universal.altMediumColor
            font.pixelSize: 24
            width: 32
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: tc2
            afficheur: tc2_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bFramerateTc2
            buttonText: tc2_aff_4.framerate + "fps"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 8
            backg.implicitHeight: 32
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // Résultat
        // ------------------------------------------------------------
        FieldResult {
            text: "RESULT"
            Layout.preferredWidth: 80
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }
        FieldInput {
            id: result
            text: "..:..:..:.."
            afficheur: result_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bMem
            buttonText: "MEM"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 8
            backg.implicitHeight: 32
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // Zone vide en bas
        // ------------------------------------------------------------
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            color: "transparent"
            Image {
                id: imagette
                width: 80
                height: 80
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Images/TiCalcul.png"
                anchors.centerIn: parent
            }
        }
        Item {
            id: emptySpace
            Layout.preferredHeight: 85
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.rowSpan: 1
            Layout.columnSpan: 2
        }
    }
}
