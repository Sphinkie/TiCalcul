import QtQuick
import QtQuick.Controls.Universal


/*! Popup ABOUT
 *
 * Ce popup affiche l'Auteur, l'année et le numéro de version.
 * Le numéro de version est aussi dans : \c CMakeLists.txt + \c Config.xml + \c Package.xml + \c Doxyfile
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
