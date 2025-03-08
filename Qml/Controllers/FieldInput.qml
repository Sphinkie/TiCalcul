import QtQuick
import TiCalcul

import "../Vues"

FieldInputForm {

    property Afficheur afficheur
    onClicked: {
        afficheurActif.name = TC1_aff_2
        console.log("FieldInput clicked - set TC1_aff_2")
    }
}
