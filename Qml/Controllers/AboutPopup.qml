import QtQuick
import QtQuick.Controls.Universal

/* ********************************************************************************************************** */


/*!
  \qmltype AboutPopup
  \inqmlmodule QTiCalcul
  \brief Ce popup affiche l'Auteur, l'Année et le Numéro de version de l'application.

  \note Le Numéro de Version est aussi dans les fichiers: \c CMakeLists.txt et \c Config.xml et \c Package.xml et \c Doxyfile.
 */
Popup {
    id: popup
    width: 200
    height: 100
    modal: true
    focus: true
    opacity: 0.8

    x: 760
    y: 56
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    background: Rectangle {
        color: Universal.altMediumHighColor
        border.color: Universal.baseMediumColor
    }
    padding: 16
    contentItem: Text {
        text: "<b>Ti Calcul</b> <br/>The ultimate timecode calculator <br/>Version 2.0  <br/>Ecrit par <b>David de Lorenzo</b> <br/>2025"
        // color: Universal.foreground
    }
}
