import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal

import "./Components"
import "./Controllers"


/*!
  \qmltype Main
  \inqmlmodule QTiCalcul
  \inherits Window
  \brief Fenêtre principale.

  La fenêtre principale contient trois zones: LeftFrame, CalculFrame et RightFrame.
  Au dessus, se trouve la TopBar avec le bouton pour faire apparaitre le AboutPopup.
  En dessous, on a le clavier numérique \l Keyboard.

  \image TiCalcul-QML-hierarchy.drawio.png
  \sa ActiveDisplay, PhysicalKeyboard, Keyboard
 */
Window {
  id: window
  width: 1000
  height: 690
  minimumWidth: 964
  minimumHeight: 612
  visible: true
  title: "TiCalcul... by David"

  Universal.background: Universal.Green // Couleur de fond.
  Universal.foreground: Universal.Amber // On utilise cette couleur pour les boutons. (Par défaut, ils seraient en background foncé).
  Universal.accent: Universal.Orange // On utilise cette couleur pour les HMSI incorrects.
  Universal.theme: Universal.Light // ou: Dark

  // ----------------------------------------------------------------
  // Page principale
  // ----------------------------------------------------------------
  Rectangle {
    id: pagePrincipale
    anchors.top: parent.top
    anchors.fill: parent
    color: Universal.background
    // ------------------------------------------------------------
    ActiveDisplay {
      id: afficheurActif
      objectName: "afficheurActif"
      signal activeDisplay(string afficheur)
    }
    // ------------------------------------------------------------
    // Gestionnaire de clavier.
    // On initialise le focus dessus.
    // ------------------------------------------------------------
    PhysicalKeyboard {
      id: physicalKeyboard
      focus: true
    }

    // ------------------------------------------------------------
    GridLayout {
      id: mainGrid
      anchors.fill: parent
      anchors.margins: 12
      columnSpacing: 0
      columns: 3

      // ----------------------------------------------------------------
      // ------------------ Top bar -------------------------------------
      // ----------------------------------------------------------------
      TopBar {
        id: topbar
        Layout.fillWidth: true
        Layout.fillHeight: false
        Layout.columnSpan: 3
        height: 32
      }
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

  AboutPopup {
    id: aboutPopup
  }
}
