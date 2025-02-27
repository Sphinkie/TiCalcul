import QtQuick
import QtQuick.Controls.Material

Item {
    property alias text: result.text
    Text {
        id: result
        text: qsTr("Text")
        anchors.fill: parent
        font.pixelSize: 15
        font.bold: true
        color: "grey"
    }
}
