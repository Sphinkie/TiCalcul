import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "./Components"
import "./Controllers"

Window {
    id: window
    width: 940
    height: 680
    minimumWidth: 820
    minimumHeight: 580
    visible: true
    title: "TiCalcul"
    //IconImage: "qrc:/Images/TiCalcul.ico"

    Universal.theme: Universal.Light
    Universal.accent: Universal.Cobalt
    Universal.foreground: Universal.Amber // Couleur forcée des boutons. Par défaut, ils sont en background foncé.
    Universal.background: Universal.Green // Couleur de fond

    // ----------------------------------------------------------------
    // Page principale
    // ----------------------------------------------------------------
    Rectangle {
        id: pagePrincipale

        anchors.top: parent.top
        anchors.fill: parent
        color: Universal.background
        // ----------------------------------------------------------------
        ActiveDisplay {
            id: afficheurActif
            objectName: "afficheurActif"
            signal activeDisplay(string afficheur)
        }
        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.margins: 20
            columns: 3
            rows: 2
            // ----------------------------------------------------------------
            // ------------------ Timecode TC 1 dans différentes unités -------
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
            // ------------------ Timecode TC 2 dans différentes unités -------
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
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.topMargin: 20
                Layout.rowSpan: 1
                Layout.columnSpan: 3
            }
        }
    }
}
