#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "Sources/operande.h"

/* ********************************************************************************* */
/*!
 * \brief Programme principal
 * \param argc (argument count): nombre de paramètres pointés par argv +1
 * \param argv (argument vector)
 * \return
 * ******************************************************************************** */
int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("TiCalcul");
    app.setOrganizationName("Sphinkie");
    app.setOrganizationDomain("de-lorenzo.fr");
    app.setWindowIcon(QIcon(":/Resources/images/TiCalcul.ico"));   // FIXME

    // --------------------------------------
    // On initialise nos classes
    // --------------------------------------
    Operande operande_tc1("TC1");
    Operande operande_tc2("TC2");

    // --------------------------------------
    // Initialisation du moteur:
    // --------------------------------------
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    // --------------------------------------
    // On ajoute au contexte les classes qui ont des property QML
    // --------------------------------------
    context->setContextProperty("operandeTC1", &operande_tc1);
    operande_tc1.registerContext(context);
    operande_tc2.registerContext(context);

    // --------------------------------------
    // Connexion des signaux
    // --------------------------------------
    // Sortie en cas de bug.
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreationFailed, &app, []()
                     {
                         QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    operande_tc1.setValeurPivot(28650000);
    operande_tc2.setValeurPivot(87545412880);

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
