import QtQuick
import QtQuick.Controls.Universal

/* ********************************************************************************************************** */


/*!
  \qmltype Bloc
  \inqmlmodule QTiCalcul
  \brief Un petit rectangle, visible ou non à l'écran, pour remplir un espace.
 */
Rectangle {


    /*! \qmlproperty bool Bloc::hidden
        Si \c true, le carré est transparent, sinon il est en \c altMediumHighColor.
    */
    property bool hidden: true

    width: 20
    height: 40
    color: hidden ? "transparent" : Universal.altMediumHighColor
}
