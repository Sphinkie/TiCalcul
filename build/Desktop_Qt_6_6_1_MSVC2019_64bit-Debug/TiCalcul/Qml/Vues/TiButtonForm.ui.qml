import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Universal


/*
//import QtQuick.Controls.Material    // pas de hovering sur les boutons
//import QtQuick.Controls.Windows     // avec hovering (looks native on Windows) - see Using Styles in Qt Quick Controls. - non custmisable. en cours de dev.
// import QtQuick.Controls.Universal  // sans hovering ( Microsoft Universal Design)
//import QtQuick.Controls.Fusion      // The Fusion style is a desktop-oriented style.
// import QtQuick.Controls.Styles     // nécessite des styles
*/
import "../Components"

Button {
    id: button
    text: "button" // default value

    //    height: 32
    contentItem: Text {
        text: button.text
        color: button.down ? "black" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        font.bold: false
        font.letterSpacing: 2
    }

    background: Rectangle {
        // color: button.checked ? TiStyle.chipBackgroundColor : TiStyle.zoneBackgroundColor.lighter(1.1)
        color: Universal.foreground
        radius: 3
    }
}
