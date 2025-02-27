import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import "./Qml/Components"

Window {
    width: 480
    height: 800
    minimumWidth: 380
    minimumHeight: 600
    visible: true
    title: "TiCalcul"

    Material.theme: Material.light
    Material.accent: Material.Orange
    //    Material.variant: Material.Normal // Dense
    Material.primary: Material.Red
    Material.foreground: Material.Teal
    Material.background: Material.Green

    // ----------------------------------------------------------------
    // Page principale
    // ----------------------------------------------------------------
    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.fill: parent
        // ----------------------------------------------------------------
        // Onglets
        // ----------------------------------------------------------------
        Rectangle {
            id: tabRectangle
            width: parent.width
            Layout.preferredHeight: 50
            Layout.fillWidth: true

            TabBar {
                id: tabBar
                width: parent.width
                font.pointSize: 16
                font.bold: true
                TabButton {
                    id: tabCalcul
                    text: qsTr("CALCUL")
                }
                TabButton {
                    id: tabConvert
                    text: qsTr("CONVERT")
                }
            }
        }
        // ----------------------------------------------------------------
        // Contenu de l'onglet
        // ----------------------------------------------------------------
        StackLayout {
            id: tabbedPage
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: tabBar.currentIndex

            // ------------------ CALCUL TAB -----------------------------
            CalculTab {
                id: calculTab
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            // ------------------ CONVERT TAB ----------------------------
            ConvertTab {
                id: convertTab
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        // ----------------------------------------------------------------
        // Clavier
        // ----------------------------------------------------------------
        Keyboard {
            Layout.fillHeight: true
            Layout.fillWidth: true
            rows: 3
        }
    }
}
