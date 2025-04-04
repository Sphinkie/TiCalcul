@echo Run me in Qt Creator terminal .. "run environnement"

windeployqt --release --dir .\installeur\packages\sphinkie.ticalcul\data   .\build\Desktop_Qt_6_6_1_MSVC2019_64bit-Release\tiCalcul.exe


@echo Il manque l'exe 
@echo Il manque des dépendances: Qt6QmlWorkerScript.dll + Qt6QuickControls2.dll + Qt6QuickControls2Impl.dll + Qt6QuickLayouts.dll + Qt6QuickShapes.dll + Qt6QuickTemplates2.dll
@echo Il manque qml/QtQml et qml/QtQuick
@echo Mettre le VCredist dans le repertoire de l'autre package
@echo.

@echo OFF

REM OPTIONS:
REM  --dir <directory>         Output directory (instead of binary directory)
REM  --libdir <path>           Copy libraries to path.
REM  --plugindir <path>        Copy plugins to path.
REM  --release                 Assume release binaries.
REM  --pdb                     Deploy .pdb files (informations de débogage pour les exécutables Windows).
REM  --compiler-runtime        Deploy compiler runtime (Desktop only).  
REM
REM ARGUMENT:
REM  [files]                   Binaries or directory containing the binary
REM 
REM EXEMPLE:
REM   windeployqt --pdb tiCalcul.exe --verbose 1 --dir . --plugindir plugins --compiler-runtime


