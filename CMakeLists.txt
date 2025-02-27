cmake_minimum_required(VERSION 3.16)

project(TiCalcul VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appTiCalcul
    main.cpp
)

qt_add_qml_module(appTiCalcul
    URI TiCalcul
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES TiCalcul.qrc
        RESOURCES Resources/images/TiCalcul.ico
        QML_FILES
        QML_FILES
        QML_FILES
        QML_FILES
        QML_FILES Qml/Controllers/TiButton.qml
        QML_FILES Qml/Vues/TiButtonForm.ui.qml
        QML_FILES Qml/Controllers/KeyboardKey.qml
        QML_FILES
        QML_FILES
        QML_FILES Qml/Vues/KeyboardKeyForm.ui.qml
        RESOURCES Resources/images/TiCalcul_black.ico
        QML_FILES Qml/Components/Keyboard.qml
        QML_FILES Qml/Components/ConvertTab.qml
        QML_FILES Qml/Components/CalculTab.qml
        QML_FILES Qml/Components/TiStyle.qml
        QML_FILES Qml/Components/FieldResult.qml
        QML_FILES Qml/Components/FieldInput.qml
        QML_FILES Qml/Components/FieldLabel.qml
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
