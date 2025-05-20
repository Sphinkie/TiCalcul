import QtQuick
import QtQuick.Controls.Universal

/* ********************************************************************************************************** */


/*!
  \qmltype AboutPopup
  \inqmlmodule QTiCalcul
  \brief Ce popup affiche l'Auteur, l'Année et le Numéro de version de l'application.

  Le popup contient aussi le switch pour change de mode clair ou sombre. \br
  \note Le Numéro de Version est aussi dans les fichiers: \c CMakeLists.txt et \c Config.xml et \c Package.xml (et \c Doxyfile).
 */
Popup {
  id: popup
  width: 200
  height: 140
  modal: true
  focus: true
  opacity: 0.85

  x: 760
  y: 46
  closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

  background: Rectangle {
    color: Universal.altMediumHighColor
    border.color: Universal.baseMediumColor
  }

  padding: 4
  contentItem: Column {

    Switch {
      id: darkmode
      text: "Dark mode"
      checked: false // Etat initial
      onClicked: window.Universal.theme = checked ? Universal.Dark : Universal.Light
    }

    Text {
      padding: 8
      text: "<b>Ti Calcul</b> <br/>The ultimate timecode calculator <br/>Version 2.3  <br/>Ecrit par <b>David de Lorenzo</b> <br/>2025"
      // color: Universal.foreground
    }
  }
}
