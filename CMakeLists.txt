cmake_minimum_required(VERSION 3.16)

project(TiCalcul VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)   # Auto use QRC resource File

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/Resources/appicon.rc")

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appTiCalcul
    main.cpp
    ${app_icon_resource_windows}
)

qt_add_qml_module(appTiCalcul
    URI TiCalcul
    VERSION 1.0
        RESOURCES Resources/TiCalcul.qrc

        QML_FILES Qml/Main.qml
        QML_FILES Qml/Vues/TiButton.ui.qml
        QML_FILES Qml/Vues/SquareButton.qml
        QML_FILES Qml/Vues/KeyboardForm.ui.qml
        QML_FILES Qml/Vues/LeftFrameForm.ui.qml
        QML_FILES Qml/Vues/RightFrameForm.ui.qml
        QML_FILES Qml/Vues/FieldInputForm.ui.qml
        QML_FILES Qml/Vues/KeyboardKeyForm.ui.qml
        QML_FILES Qml/Vues/CalculFrameForm.ui.qml

        QML_FILES Qml/Controllers/Keyboard.qml
        QML_FILES Qml/Controllers/LeftFrame.qml
        QML_FILES Qml/Controllers/FieldInput.qml
        QML_FILES Qml/Controllers/RightFrame.qml
        QML_FILES Qml/Controllers/CalculFrame.qml

        QML_FILES Qml/Components/FieldLabel.qml
        QML_FILES Qml/Components/FieldResult.qml
        QML_FILES Qml/Components/ActiveDisplay.qml

        SOURCES Sources/unites.h Sources/unites.cpp
        SOURCES Sources/operande.h Sources/operande.cpp
        SOURCES Sources/afficheur.h Sources/afficheur.cpp
        SOURCES Sources/converter.h Sources/converter.cpp
        SOURCES Sources/calculateur.h Sources/calculateur.cpp
        QML_FILES Qml/Components/Bloc.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTiCalcul PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTiCalcul
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTiCalcul
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appTiCalcul
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
