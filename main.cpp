#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "Sources/operande.h"

/* ********************************************************************************* */
/*!
 * \brief Programme principal
 * \param argc (argument count): nombre +1 de paramètres de argv
 * \param argv (argument vector)
 * \return 0 si sortie normale, -1 sinon.
 * ******************************************************************************** */
int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("TiCalcul");
    app.setOrganizationName("Sphinkie");
    app.setOrganizationDomain("de-lorenzo.fr");
    app.setWindowIcon(QIcon(":images/TiCalcul.ico"));   // FIXME : l'icone n'apparait pas

    // --------------------------------------
    // On initialise nos classes
    // --------------------------------------
    Operande operande_tc1("TC1");
    Operande operande_tc2("TC2");
    Operande operande_res("RESULT");

    // --------------------------------------
    // Initialisation du moteur:
    // --------------------------------------
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    // ------------------------------------------------------------
    // On ajoute au contexte les classes qui ont des property QML
    // ------------------------------------------------------------
    context->setContextProperty("operandeTC1", &operande_tc1);
    context->setContextProperty("operandeTC2", &operande_tc2);
    context->setContextProperty("operandeRES", &operande_res);
    operande_tc1.registerContext(context);
    operande_tc2.registerContext(context);
    operande_res.registerContext(context);

    // ------------------------------------------------------------
    // On ajoute le type Afficheur au contexte QML
    // ------------------------------------------------------------
    qmlRegisterType<Afficheur>("TiCalcul", 1, 0, "Afficheur");

    // --------------------------------------
    // Connexion des signaux
    // --------------------------------------
    // Sortie en cas de bug.
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreationFailed, &app, []()
                     {
                         QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

//    operande_tc1.setValeurPivot(28650000);
//    operande_tc2.setValeurPivot(87545412880);
//    operande_res.setValeurPivot(120000000);

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
