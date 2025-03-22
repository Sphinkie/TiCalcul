import QtQuick
import QtQuick.Controls.Universal

Rectangle {
    property bool hidden: true

    width: 20
    height: 40
    color: hidden ? "transparent" : Universal.altMediumHighColor
}
