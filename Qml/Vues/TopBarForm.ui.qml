import QtQuick
import QtQuick.Controls 2.15

Item {
    id: _item
    property alias btAbout: btAbout
    implicitWidth: 400

    Button {
        id: btAbout
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 0
        anchors.topMargin: 0
        display: AbstractButton.IconOnly
        icon.source: "qrc:/Images/settings_amb.png"
        icon.height: 28
        icon.width: 28

        background: Rectangle {
            color: "transparent"
        }
    }
}
