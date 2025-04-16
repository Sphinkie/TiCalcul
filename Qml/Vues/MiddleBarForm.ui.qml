import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15


/*!
  \qmltype MittelBarForm
  \inqmlmodule QTiCalcul
  \brief Ligne discrète avec le bouton btHideKb, pour masquer et afficher le clavier \l Keyboard.
 */
Item {
  /*! Alias pour controller le bouton btHideKb */
  property alias btHideKb: btHideKb

  // ----------------------------------------------------------------
  // Bouton Hide Keyboard
  // ----------------------------------------------------------------
  Button {
    id: btHideKb

    anchors.right: parent.right
    display: AbstractButton.IconOnly
    icon.source: keyboard.visible ? "qrc:/Images/close.png" : "qrc:/Images/open.png"
    icon.height: 28
    icon.width: 28

    background: Rectangle {
      color: "transparent"
    }
  }
}
