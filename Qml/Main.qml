import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "./Components"
import "./Controllers"

Window {
    width: 920
    height: 680
    minimumWidth: 820
    minimumHeight: 580
    visible: true
    title: "TiCalcul"

    Universal.theme: Universal.Light
    Universal.accent: Universal.Cobalt
    Universal.foreground: Universal.Amber // Couleur forcée des boutons. Par défaut, ils sont en background foncé.
    Universal.background: Universal.Green // Couleur de fond


    /*
      5 Nuances claires de la couleur de background
    Universal.altHighColor       = blanc                  ... fond pour input
    Universal.altMediumHighColor = background très clair  ... fond pour input
    Universal.altMediumColor     = background clair       ... fond pour results
    Universal.altMediumLowColor  = background clair
    Universal.altLowColor        = background atténué
    */


    /*
      5 Nuances foncées de la couleur de background
    Universal.baseLowColor          = background assombri       = Universal.chromeBlackLowColor
    Universal.baseMediumLowColor    = background sombre         = chromeBlackMediumLowColor
    Universal.baseMediumColor       = background sombre++                                            ... textes pour labels
    Universal.baseMediumHighColor   = background quasi noir     = chromeBlackMediumColor
    Universal.baseHighColor         = noir                      = chromeBlackHighColor
    */


    /*
      2 nuances de backgound
        Universal.listMediumColor   = background foncé = identique baseLowColor
        Universal.listLowColor      = background clair = identique altLowColor
     */


    /*
     6 nuances de gris
    Universal.chromeWhiteColor          = blanc
    Universal.chromeLowColor            = blanc-gris
    Universal.chromeMediumLowColor      = blanc-gris
    Universal.chromeMediumColor         = gris clair        ... boutons du clavier
    Universal.chromeHighColor           = gris moyen        ... boutons du clavier
    Universal.chromeAltLowColor         = gris très foncé   ... texte afficheurs

    Universal.chromeDisabledHighColor   = gris clair        ... texte boutons du clavier
    Universal.chromeDisabledLowColor    = gris soutenu

    */

    // ----------------------------------------------------------------
    // Page principale
    // ----------------------------------------------------------------
    Rectangle {
        anchors.top: parent.top
        anchors.fill: parent
        color: Universal.background
        // ----------------------------------------------------------------
        ActiveDisplay {
            id: afficheurActif
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
