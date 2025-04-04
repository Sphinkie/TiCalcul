#include <QQmlEngine>
#include "operande.h"


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \class Operande
 * \inmodule TiCalcul
 * \brief La class Operande gère la "valeur pivot" (cad en microsecondes) de l'opérande TC1 ou de TC2.
 *
 */


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief Constructeur.
 * Crée les 8 Afficheur de cet opérande, et les connecte pour leur envoyer un signal
 * à chaque modification de la valeur pivot.
 * \note L'afficheur NTSC est désactivé pour le moment.
 *
 * \a name: Le nom de l'operande: "tc1" ou "tc2" ou "result". \br
 * \a parent: Pointeur sur QObject parent. \br
 */
Operande::Operande(QString name, QObject *parent): QObject(parent)
{
    this->setObjectName(name);
    a1 = new Afficheur(Unites::SECONDS, this);
    a2 = new Afficheur(Unites::MILLISECONDS, this);
    a3 = new Afficheur(Unites::MICROSECONDS, this);
    a4 = new Afficheur(Unites::HMSI, this);
    a5 = new Afficheur(Unites::DHMSM, this);
    a6 = new Afficheur(Unites::FRAMES_25, this);
    a7 = new Afficheur(Unites::FRAMES_50, this);
    //a8 = new Afficheur(Unites::FRAMES_NTSC);

    // Navigation : N S E W
    if (name == "tc1") {
        a1->setNavigation(a1,a2,a4,a1);  // HMSI à droite
        a2->setNavigation(a1,a3,a2,a2);
        a3->setNavigation(a2,a6,a3,a3);
        a6->setNavigation(a3,a7,a6,a6);
        a7->setNavigation(a6,a7,a7,a7);
        a4->setNavigation(a4,a4,a4,a1);   // SECONDS à gauche
    }
    else if (name == "tc2") {
        a1->setNavigation(a1,a2,a1,a1);
        a2->setNavigation(a1,a3,a2,a2);
        a3->setNavigation(a2,a6,a3,a4);   // HMSI à gauche
        a6->setNavigation(a3,a7,a6,a6);
        a7->setNavigation(a6,a7,a7,a7);
        a4->setNavigation(a4,a4,a3,a4);   // MICROSECS à droite
    }
    else {                                // Pas de mouvement pour les autres
        a1->setNavigation(a1,a1,a1,a1);
        a2->setNavigation(a2,a2,a2,a2);
        a3->setNavigation(a3,a3,a3,a3);
        a6->setNavigation(a6,a6,a6,a6);
        a7->setNavigation(a7,a7,a7,a7);
        a4->setNavigation(a4,a4,a4,a4);
    }

    // On signale à l'afficheur HMSI qu'il a le focus.
    // (Ce serait mieux via le QML, mais il semble instancié trop tot).
    a4->activeDisplay("tc1_HMSI");

    QList<Afficheur*> afficheurs = {a1, a2, a3, a3, a4, a5, a6, a7};
    QList<Afficheur*>::iterator it;

    // Connexions pour les afficheurs instanciées
    for (it=afficheurs.begin(); it != afficheurs.end();  it++)
    {
        // Envoi de la valeur pivot aux afficheurs.
        QObject::connect(this, SIGNAL(valeurPivotChanged(qint64,bool)), *it, SLOT(setValue(qint64,bool)));
        // Signale aux afficheurs que la valeur pivot a été effacée.
        QObject::connect(this, SIGNAL(valeurPivotCleared()), *it, SLOT(clearValue()));
        // Réception des modifications de la valeur pivot.
        QObject::connect(*it, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    }
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief Renvoie la valeur Pivot (en microsecondes).
 */
qint64 Operande::valeurPivot() const
{
    return mValeurPivot;
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * Ce slot recoit une nouvelle valeur pivot d'un Afficheur et la propage à tous les Afficheurs.
 *
 * La \a newValeurPivot est exprimées en microsecondes, et le paramètre \a force précise
 * s'il faut la prendre en compte même si le champ est en cours d'édition.
 *
 * Peut aussi être positionné par le calculateur. \br
 * Réception du signal Afficheur::setValeurPivot(). \br
 * Envoie le signal Operande::valeurPivotChanged() aux Afficheur. \br
 * Le slot de réception des Afficheur est setValue() \br
 */
void Operande::setValeurPivot(const qint64 newValeurPivot, const bool force)
{
    if (newValeurPivot > this->mMaxValue)
    {
        qDebug("ERROR: msg_max_reached: discard candidate %d ! ", newValeurPivot);
    }
    else
    {
        qDebug() << this->objectName() << "received new pivot (us)" << newValeurPivot << force;
        mValeurPivot = newValeurPivot;
        emit valeurPivotChanged(newValeurPivot, force);
    }
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief SLOT : Vide la valeur pivot, et efface la valeur de tous les Afficheur.
 * \sa Afficheur::clearValue()
 */
void Operande::clearValeurPivot()
{
    qDebug()<< this->objectName() << "::clearValeurPivot";
    mValeurPivot = 0;
    emit valeurPivotCleared();
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief Enregistre les Afficheur dans le contexte QML, pour pouvoir les afficher.
 *
 * \b Note Les property names seront du type "tc1_aff_1". \br
 * \a context: Le rootContext de l'application.
 */
void Operande::registerContext(QQmlContext* context)
{
    context->setContextProperty(this->objectName()+"_aff_1", a1);
    context->setContextProperty(this->objectName()+"_aff_2", a2);
    context->setContextProperty(this->objectName()+"_aff_3", a3);
    context->setContextProperty(this->objectName()+"_aff_4", a4);
    context->setContextProperty(this->objectName()+"_aff_5", a5);  // D+HMSmm
    context->setContextProperty(this->objectName()+"_aff_6", a6);
    context->setContextProperty(this->objectName()+"_aff_7", a7);
    //context->setContextProperty(this->objectName()+"_aff_8", a8);
}

/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief La fonction setPartner recoit un pointeur sur l'objet Operande partenaire \a partner (=TC2), et crée  un
 * "apairage" entre chacun de ses afficheurs et les afficheurs de l'operande partenaire TC2.
 */
void Operande::setPartner(Operande *partner)
{
    a1->findPartner(partner->objectName());
    a2->findPartner(partner->objectName());
    a3->findPartner(partner->objectName());
    a4->findPartner(partner->objectName());
    a5->findPartner(partner->objectName());
    a6->findPartner(partner->objectName());
    a7->findPartner(partner->objectName());
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/*!
 * \brief Cette fonction crée des connexions slot-signal.
 *
 * Cree des connexions entre l'objet QML "afficheurActif" et tous les Afficheurs.
 * Ainsi, lorsque l'Afficheur actif change, tous les afficheurs sont informés.
 * \a engine: un pointeur sur le moteur QML.
 */
void Operande::connectActiveDisplay(QQmlApplicationEngine* engine)
{
    // On trouve l'objet QML nommé "afficheurActif"
    QObject* qmlItem = engine->rootObjects().constFirst()->findChild<QObject*>("afficheurActif");
    // On le connecte à tous les afficheurs.
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a1, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a2, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a3, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a4, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a5, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a6, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a7, SLOT(activeDisplay(QString)));
}
