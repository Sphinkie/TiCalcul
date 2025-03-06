import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Universal

import "./Components"

Window {
    width: 800
    height: 680
    minimumWidth: 600
    minimumHeight: 580
    visible: true
    title: "TiCalcul"

    Universal.theme: Universal.Light
    Universal.accent: Universal.Orange
    Universal.foreground: Universal.Amber
    Universal.background: Universal.Green

    // ----------------------------------------------------------------
    // Page principale
    // ----------------------------------------------------------------
    Rectangle {
        anchors.top: parent.top
        anchors.fill: parent
        color: Universal.background
        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.margins: 20
            columns: 3
            rows: 2
            // ----------------------------------------------------------------
            // ------------------ Valeurs Converties 1 ------------------------
            // ----------------------------------------------------------------
            LeftFrame {
                id: leftFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            // ----------------------------------------------------------------
            // ------------------ Zone de calcul ------------------------------
            // ----------------------------------------------------------------
            CalculFrame {
                id: calculFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            // ----------------------------------------------------------------
            // ------------------ Valeurs Converties 2 ------------------------
            // ----------------------------------------------------------------
            RightFrame {
                id: rightFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            // ----------------------------------------------------------------
            // ------------------ Clavier -------------------------------------
            // ----------------------------------------------------------------
            Keyboard {
                Layout.rowSpan: 1
                Layout.columnSpan: 3
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.topMargin: 20
            }
        }
    }
}
