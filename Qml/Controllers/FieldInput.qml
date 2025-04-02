import QtQuick
import TiCalcul

import "../Vues"


/* ********************************************************************************
 * \brief Mémorise l'afficheur actif, lors d'un click sur un afficheur FieldInput.
 * Si des touches clavier sont recues lorsque le bouton a le focus,
 * on les forwarde au gestionnaire de clavier.
 ***********************************************************************************/
FieldInputForm {
    id: control
    property bool bold: false

    Keys.onPressed: event => {
                        if ((event.key === Qt.Key_C)
                            && (event.modifiers & Qt.ControlModifier)) {
                            textedit.text = displaytext
                            textedit.selectAll()
                            textedit.copy()
                            console.log("Ctrl+C")
                            event.accepted = true
                        }
                    }

    // Les touches du clavier sont forwardées vers le Gestionnaire
    Keys.forwardTo: [physicalKeyboard]

    // Un item cliqué devient l'afficheur actif
    onClicked: {
        afficheurActif.afficheur = afficheur
    }

    // Zone tampon vers le clipboard
    TextEdit {
        id: textedit
        visible: false
    }
}
