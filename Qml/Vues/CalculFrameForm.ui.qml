import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "../Components"
import "../Controllers"

/* *********************************************************************************** */

/*!
  \qmltype CalculFrameForm
  \inqmlmodule QTiCalcul
  \brief Affiche les \l Operande en HMSI ainsi que le résultat du calcul, une imagette et un éventuel message.
  
  \sa Bloc, FieldResult, SquareButton, FieldInput, TiButton
*/
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
            Layout.minimumWidth: 120 // va s'appliquer à toute la colonne
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
        // Opérateur
        // ------------------------------------------------------------
        Bloc {}
        Bloc {
            Layout.fillWidth: true
            hidden: false
            color: Universal.altMediumColor
        }
        FieldResult {
            text: calculateur.operateur
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.rowSpan: 1
            Layout.columnSpan: 2
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
        // On masque la ligne si l'opérateur est le complément à 24h
        // ------------------------------------------------------------
        Bloc {}
        FieldResult {
            id: labelTC2
            text: "TC2"
            color: Universal.altMediumHighColor
            opacity: calculateur.operateur === "Cmplt" ? 0 : 100
            Layout.preferredWidth: 52
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        SquareButton {
            id: bRectifyTc2
            text: "\u27f3"
            color: Universal.altMediumHighColor
            opacity: calculateur.operateur === "Cmplt" ? 0 : 100
            font.pixelSize: 24
            width: 32
            Layout.fillHeight: false
            Layout.fillWidth: false
        }
        FieldInput {
            id: tc2
            afficheur: tc2_aff_4
            opacity: calculateur.operateur === "Cmplt" ? 0 : 100
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        Rectangle {
            id: rectangle1
            opacity: calculateur.operateur === "Cmplt" ? 0 : 100
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
        Text {
            id: msgArea
            Layout.preferredHeight: 85
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.topMargin: 8
            Layout.rowSpan: 1
            Layout.columnSpan: 2
            text: calculFrame.msgText
            font.pixelSize: 12
        }
    }
}
