@echo Run me in Qt Creator terminal .. "run environnement"
@echo Need QT_INSTALL_DOCS=C:/Qt/Docs/Qt-6.9.0 dans les Build et Run Environnement

qdoc ticalcul.qdocconf

qhelpgenerator docs/qdoc/html/ticalcul.qhp -o ticalcul.qch
