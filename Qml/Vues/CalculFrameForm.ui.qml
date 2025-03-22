import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"
import "../Controllers"

Item {
    property alias tc1: tc1
    property alias tc2: tc2
    property alias bMem: bMem
    property alias bSwap: bSwap
    property alias bFramerateTc1: bFramerateTc1
    property alias bFramerateTc2: bFramerateTc2
    property alias bRectifyTc1: bRectifyTc1
    property alias bRectifyTc2: bRectifyTc2

    GridLayout {
        id: zoneResults
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        columns: 5

        // ------------------------------------------------------------
        // 1ere ligne - TC1 en HMSI
        // ------------------------------------------------------------
        Bloc {
            hidden: false
        }
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
            Layout.rightMargin: 8
            buttonText: tc1_aff_4.framerate + "fps"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 6
            backg.implicitHeight: 28
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // Operande
        // ------------------------------------------------------------
        Bloc {}
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
            Layout.rightMargin: 8
            buttonText: "⇵"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 6
            backg.implicitHeight: 28
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // 2eme ligne - TC2 en HMSI
        // ------------------------------------------------------------
        Bloc {}
        FieldResult {
            id: labelTC2
            text: "TC2"
            color: Universal.altMediumHighColor
            Layout.preferredWidth: 52
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        SquareButton {
            id: bRectifyTc2
            text: "\u27f3"
            color: Universal.altMediumHighColor
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
        Rectangle {
            id: rectangle1
            implicitHeight: 40
            implicitWidth: 86
            Layout.fillHeight: false
            Layout.fillWidth: false
            color: Universal.altMediumHighColor
            TiButton {
                id: bFramerateTc2
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 6
                anchors.topMargin: 4
                buttonText: tc2_aff_4.framerate + "fps"
                backg.implicitHeight: 28
                backg.implicitWidth: 72
            }
        }

        // ------------------------------------------------------------
        // Résultat
        // ------------------------------------------------------------
        Bloc {}
        FieldResult {
            text: "RESULT"
            Layout.preferredWidth: 80
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }
        FieldInput {
            id: result
            bold: true
            text: "..:..:..:.."
            enabled: false
            afficheur: result_aff_4
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        TiButton {
            id: bMem
            Layout.rightMargin: 8
            buttonText: "MEM"
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.leftMargin: 6
            backg.implicitHeight: 28
            backg.implicitWidth: 72
        }

        // ------------------------------------------------------------
        // Zone vide en bas
        // ------------------------------------------------------------
        Bloc {}
        Rectangle {
            id: rectangle
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            color: "transparent"
            Image {
                id: imagette
                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 8
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Images/TiCalcul.png"
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

        Bloc {
            id: bloc
        }

        Bloc {
            id: bloc1
        }
    }
}
