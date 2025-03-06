import QtQuick
import "../Vues"

// Il faut mettre un Item en premier niveau sinon les Layout ne se gèrent pas bien.
Item {
    property string buttonText

    TiButtonForm {

        onClicked: {

            console.log("TiButton clicked ! ")
            operandeTC1.clear();
    }
}
}

