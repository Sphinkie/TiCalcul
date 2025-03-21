#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "Sources/operande.h"
#include "Sources/calculateur.h"

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
    app.setWindowIcon(QIcon(":Images/TiCalcul.ico"));  // TopLeft icon

    qDebug() <<"max qint64 on this system" << std::numeric_limits<qint64>::max();   // 9 223 372 036 854 775 807

    // --------------------------------------
    // On initialise nos classes
    // --------------------------------------
    Operande operande_tc1("tc1", &app);
    Operande operande_tc2("tc2", &app);
    Operande operande_res("result", &app);
    Calculateur calculateur(&operande_tc1, &operande_tc2, &operande_res, &app);

    // --------------------------------------
    // Initialisation du moteur:
    // --------------------------------------
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    // ------------------------------------------------------------
    // On ajoute les classes qui ont des property au contexte QML
    // ------------------------------------------------------------
    context->setContextProperty("operandeTC1", &operande_tc1);
    context->setContextProperty("operandeTC2", &operande_tc2);
    context->setContextProperty("operandeRES", &operande_res);
    context->setContextProperty("calculateur", &calculateur);

    // ------------------------------------------------------------
    // Chaque operande ajoute ses afficheurs au contexte QML
    // ------------------------------------------------------------
    operande_tc1.registerContext(context);
    operande_tc2.registerContext(context);
    operande_res.registerContext(context);

    // ------------------------------------------------------------
    // Connexions
    // ------------------------------------------------------------
    // Les operandes signalent au calculateur si leur valeur pivot change.
    QObject::connect(&operande_tc1, SIGNAL(valeurPivotChanged(qint64,bool)), &calculateur, SLOT(onValeurPivotChanged()));
    QObject::connect(&operande_tc2, SIGNAL(valeurPivotChanged(qint64,bool)), &calculateur, SLOT(onValeurPivotChanged()));

    // ------------------------------------------------------------
    // On ajoute le type Afficheur au contexte QML.
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

    // --------------------------------------
    // Démarrage du moteur.
    // Load "Main.qml" from the module "TCcalcul".
    // --------------------------------------
    engine.loadFromModule("TiCalcul", "Main");

    operande_tc1.connectActiveDisplay(&engine);
    operande_tc2.connectActiveDisplay(&engine);
    // --------------------------------------
    // Exécution de QML
    // --------------------------------------
    return app.exec();
}
