import QtQuick
import QtQuick.Controls.Windows
import "../Vues"


/*
Pressed:  event is generated when you push down the mouse button
Released: event is generated when you release the mouse button (which has been pressed down before)
Clicked:  event is generated when a mouse button Pressed & Released.

* @see https://doc.qt.io/qt-5/qtquickcontrols2-customize.html#customizing-button
*/
KeyboardKeyForm {

    onClicked: console.log("KeyboardKey clicked !")
}
