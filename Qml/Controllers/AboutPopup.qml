import QtQuick
import QtQuick.Controls.Universal

Popup {
    id: popup
    width: 200
    height: 100
    modal: true
    focus: true
    opacity: 0.7

    x: 760
    y: 56
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    background: Rectangle {
        color: Universal.altMediumHighColor
        border.color: Universal.baseMediumColor
    }
    // anchors.centerIn: Overlay.overlay
    padding: 16
    contentItem: Text {
        text: "<b>Ti Calcul</b> <br/>The ultimate timecode calculator <br/>Version 1.0  <br/>Ecrit par <b>David de Lorenzo</b> <br/>2025"
        // color: Universal.foreground
    }
}
