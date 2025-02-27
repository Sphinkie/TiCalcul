import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
//import QtQuick.Controls.Material // pas de hovering sur le sboutons
//import QtQuick.Controls.Windows  // avec hovering ( looks native on Windows) - see Using Styles in Qt Quick Controls. - non custmisable. en cours de dev.
// import QtQuick.Controls.Universal  // sans hovering ( Microsoft Universal Design)
// The Fusion style is a desktop-oriented style.
//import QtQuick.Controls.Fusion

// import QtQuick.Controls.Styles // nécessite des tyles
import "../Components"

Button {
    id: bt

    //    height: 32
    contentItem: Text {
        text: bt.text
        color: bt.down ? "black" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 16
        font.bold: false
        //        font.letterSpacing: 2
    }

    background: Rectangle {
        // color: bt.checked ? TiStyle.chipBackgroundColor : TiStyle.zoneBackgroundColor.lighter(1.1)
        color: "orange"
        radius: 3
    }
}
