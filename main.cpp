#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>


/* ********************************************************************************* */
/*!
 * \brief Programme principal
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("TiCalcul");
    app.setOrganizationName("Sphinkie");
    app.setOrganizationDomain("de-lorenzo.fr");
    app.setWindowIcon(QIcon(":/images/TiCalcul.ico"));

    // --------------------------------------
    // Initialisation du moteur:
    // --------------------------------------
    QQmlApplicationEngine engine;

    // --------------------------------------
    // Connexion des signaux
    // --------------------------------------
    // Sortie en cas de bug.
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreationFailed, &app, []()
                     {
                         QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    // --------------------------------------
    // Démarrage du moteur.
    // Load "Main.qml" from the module "TCcalcul".
    // --------------------------------------
    engine.loadFromModule("TiCalcul", "Main");

    // --------------------------------------
    // Exécution de QML
    // --------------------------------------
    return app.exec();
}
