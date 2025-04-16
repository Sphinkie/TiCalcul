#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "Sources/operande.h"
#include "Sources/calculateur.h"

/* ********************************************************************************* */
/* Entête pour la QDOC                                                               */
/* ********************************************************************************* */
/*!
    \module TiCalcul
    \title Timecode Calculator
    \brief The ultimate timecode Calculator.

    \b {TiCalcul convertit, additionne et soustrait des timecodes, en particulier en millisecondes
    et en images, ce qui est spécialement utile dans les métiers de la vidéo.}

    Logiciel gratuit et sans publicité.

    TiCalcul est developpé en C++ et en QML (avec le framework Qt version 6).
    Cette documentation décrit les classes C++ et les \l {TiCalcul QML Module}{les types QML}.

    \image screenshot.png {Ecran principal de l'application}
    \startpage Timecode Calculator
*/

/* *********************************************************************************
 * Programme principal
 * *********************************************************************************
 * Retourne 0 si sortie normale, -1 sinon.
 * argc: (argument count). Nombre +1 de paramètres de argv.
 * argv: (argument vector).
 ***********************************************************************************/
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
    // On ajoute le type d'objet Afficheur au contexte QML.
    // ------------------------------------------------------------
    qmlRegisterType<Afficheur>("TiCalcul", 1, 0, "Afficheur");

    // ------------------------------------------------------------
    // Connexions
    // ------------------------------------------------------------
    // Les operandes signalent au calculateur si leur valeur pivot change.
    QObject::connect(&operande_tc1, SIGNAL(valeurPivotChanged(qint64,bool)), &calculateur, SLOT(onValeurPivotChanged()));
    QObject::connect(&operande_tc2, SIGNAL(valeurPivotChanged(qint64,bool)), &calculateur, SLOT(onValeurPivotChanged()));

    // Etablit les "apairages" entre les afficheurs de TC1 et de TC2.
    operande_tc1.setPartner(&operande_tc2);
    operande_tc2.setPartner(&operande_tc1);

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
    // Load "Main.qml" from the module "TCcalcul". (Nom du projet Qt)
    // --------------------------------------
    engine.loadFromModule("TiCalcul", "Main");

    operande_tc1.connectActiveDisplay(&engine);
    operande_tc2.connectActiveDisplay(&engine);
    // --------------------------------------
    // Exécution de QML
    // --------------------------------------
    return app.exec();
}
