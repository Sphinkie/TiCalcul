import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15


/*!
  \qmltype TopBarForm
  \inqmlmodule QTiCalcul
  \brief Bandeau supérieur avec le nom de l'application, et le bouton pour AboutPopup.
 */
RowLayout {
  property alias btAbout: btAbout
  // implicitWidth: 800
  //width: 800
  spacing: 0

  // ----------------------------------------------------------------
  // Titre
  // ----------------------------------------------------------------
  FontLoader {
    id: titlefont
    source: "qrc:/Fonts/Ericsson_GA628.ttf"
    //source: "qrc:/Fonts/Vectroid.otf"
  }
  Label {
    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
    Layout.fillWidth: true
    text: "Ti Calcul"
    font.family: titlefont.font.family
    font.weight: titlefont.font.weight
    font.styleName: titlefont.font.styleName
    font.pixelSize: 32
  }
  // ----------------------------------------------------------------
  // Bouton Settings
  // ----------------------------------------------------------------
  Button {
    id: btAbout
    Layout.alignment: Qt.AlignRight | Qt.AlignBottom
    display: AbstractButton.IconOnly
    icon.source: "qrc:/Images/settings_amb.png"
    icon.height: 28
    icon.width: 28

    background: Rectangle {
      color: "transparent"
    }
  }
}
