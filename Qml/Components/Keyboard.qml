import QtQuick
import QtQuick.Layouts
import "../Controllers"

GridLayout {
    id: keyboardGrid
    columns: 4

    KeyboardKey {
        id: key1
        buttonText: "1"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key2
        buttonText: "2"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key3
        buttonText: "3"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: keyPlus
        buttonText: "+"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key4
        buttonText: "4"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key5
        buttonText: "5"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key6
        buttonText: "6"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: keyMinus
        buttonText: "-"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key7
        buttonText: "7"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key8
        buttonText: "8"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key9
        buttonText: "9"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: keyComplt
        buttonText: "24'C"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key00
        buttonText: "00"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: key0
        buttonText: "0"
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: keyDot
        buttonText: "."
        Layout.fillWidth: true
    }
    KeyboardKey {
        id: keyDel
        buttonText: "<<"
        Layout.fillWidth: true
    }
}
