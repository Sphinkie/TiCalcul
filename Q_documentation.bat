@echo Run me in Qt Creator terminal .. "run environnement"
@echo Need QT_INSTALL_DOCS=C:/Qt/Docs/Qt-6.6.1 dans les Build et Run Environnement

qdoc TiCalcul.qdocconf

qhelpgenerator docs/qdoc/html/TiCalcul.qhp -o TiCalcul.qch
