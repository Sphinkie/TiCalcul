import QtQuick
import QtQuick.Controls.Universal


/*
//import QtQuick.Controls.Material    // pas de hovering sur les boutons
//import QtQuick.Controls.Windows     // avec hovering (looks native on Windows) - see Using Styles in Qt Quick Controls. - non custmisable. en cours de dev.
// import QtQuick.Controls.Universal  // sans hovering ( Microsoft Universal Design)
//import QtQuick.Controls.Fusion      // The Fusion style is a desktop-oriented style.
// import QtQuick.Controls.Styles     // nécessite des styles
*/
Button {
    id: button
    anchors.fill: parent
    anchors.topMargin: 8

    contentItem: Text {
        text: buttonText
        // color: button.down ? "black" : "white"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
        font.bold: false
        //font.letterSpacing: 2
    }

    background: Rectangle {
        color: button.down ? Universal.foreground.lighter(
                                 1.1) : Universal.foreground
        radius: 6
    }
}
