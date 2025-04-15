cmake_minimum_required(VERSION 3.16)

project(Q_TiCalcul VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)   # Auto use QRC resource File

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/Resources/appicon.rc")

find_package(Qt6 REQUIRED COMPONENTS Quick Core Qml)   # modif recommandée par https://doc.qt.io/qt-6/qt6-port-to-qt-add-qml-module.html

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(tiCalcul
    ${app_icon_resource_windows}
)

qt_add_qml_module(tiCalcul
    URI Q_TiCalcul
    VERSION 2.0
        RESOURCES Resources/TiCalcul.qrc
        RESOURCES TiCalcul.qdocconf

        QML_FILES Qml/Main.qml
        QML_FILES Qml/Vues/TopBarForm.ui.qml
        QML_FILES Qml/Vues/TiButtonForm.ui.qml
        QML_FILES Qml/Vues/SquareButton.ui.qml
        QML_FILES Qml/Vues/KeyboardForm.ui.qml
        QML_FILES Qml/Vues/LeftFrameForm.ui.qml
        QML_FILES Qml/Vues/RightFrameForm.ui.qml
        QML_FILES Qml/Vues/FieldInputForm.ui.qml
        QML_FILES Qml/Vues/KeyboardKeyForm.ui.qml
        QML_FILES Qml/Vues/CalculFrameForm.ui.qml

        QML_FILES Qml/Controllers/TopBar.qml
        QML_FILES Qml/Controllers/TiButton.qml
        QML_FILES Qml/Controllers/Keyboard.qml
        QML_FILES Qml/Controllers/LeftFrame.qml
        QML_FILES Qml/Controllers/AboutPopup.qml
        QML_FILES Qml/Controllers/FieldInput.qml
        QML_FILES Qml/Controllers/RightFrame.qml
        QML_FILES Qml/Controllers/CalculFrame.qml
        QML_FILES Qml/Controllers/PhysicalKeyboard.qml

        QML_FILES Qml/Components/Bloc.qml
        QML_FILES Qml/Components/FieldLabel.qml
        QML_FILES Qml/Components/FieldResult.qml
        QML_FILES Qml/Components/ActiveDisplay.qml

        SOURCES main.cpp
        SOURCES Sources/unites.h Sources/unites.cpp
        SOURCES Sources/operande.h Sources/operande.cpp
        SOURCES Sources/afficheur.h Sources/afficheur.cpp
        SOURCES Sources/converter.h Sources/converter.cpp
        SOURCES Sources/calculateur.h Sources/calculateur.cpp
)

# Mute all C++ qDebug logs - Need a Clean + Rebuild.
add_definitions(-DQT_NO_DEBUG_OUTPUT)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(tiCalcul PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tiCalcul
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(tiCalcul
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS tiCalcul
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Steps for WinDeployQt
#
#SET(BIN_DBG ${CMAKE_CURRENT_BINARY_DIR}/Debug)
#SET(BIN_REL ${CMAKE_CURRENT_BINARY_DIR}/Release)
#
#ADD_CUSTOM_COMMAND(
#  TARGET tiCalcul
#  POST_BUILD
#  COMMAND
#    CD $<$<CONFIG:Debug>:${BIN_DBG}>$<$<CONFIG:Release>:${BIN_REL}> &&
#    ${WINDEPLOYQT_EXECUTABLE} --pdb tiCalcul.exe
#       --verbose 1 --dir . --plugindir plugins --compiler-runtime
#    )
