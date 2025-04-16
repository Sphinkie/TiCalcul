@echo Run me in Qt Creator terminal .. "Run Environment"

@echo.
@echo 1: Copie de l'executable
copy .\build\Desktop_Qt_6_9_0_MSVC2022_64bit-Release\TiCalcul.exe .\installeur\packages\sphinkie.ticalcul\data\

@echo.
@echo 2: Deploiment des librairies
windeployqt --release --no-translations --qmldir .\Qml  .\installeur\packages\sphinkie.ticalcul\data

