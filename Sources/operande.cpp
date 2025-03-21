#include "operande.h"

#include <QQmlEngine>

/*! **********************************************************************************************************
 * \brief Constructeur: crée les 8 afficheurs de cet opérande, et les connecte pour leur envoyer un signal
 *        à chaque modification de la valeur pivot.
 * \note L'afficheur NTSC est désactivé pour le moment.
 * \param name: Le nom de l'operande: "tc1" ou "tc2" ou "result".
 * \param parent: Pointeur sur QObject parent.
 * ***********************************************************************************************************/
Operande::Operande(const QString name, QObject* parent)
{
    this->mName = name;
    this->setObjectName(name);

    a1 = new Afficheur(Unites::SECONDS, name, this);
    a2 = new Afficheur(Unites::MILLISECONDS, name, this);
    a3 = new Afficheur(Unites::MICROSECONDS, name, this);
    a4 = new Afficheur(Unites::HMSI, name, this);
    a5 = new Afficheur(Unites::DHMSM, name, this);
    a6 = new Afficheur(Unites::FRAMES_25, name, this);
    a7 = new Afficheur(Unites::FRAMES_50, name, this);
    //a8 = new Afficheur(Unites::FRAMES_NTSC);

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

 /*! **********************************************************************************************************
 * \brief Renvoie la valeur Pivot (en microsecondes).
 * \returns the value in microseconds.
 * ************************************************************************************************************/
qint64 Operande::valeurPivot() const
{
    return mValeurPivot;
}

/*! **********************************************************************************************************
 * \brief SLOT : Reçoit une nouvelle valeur pivot d'un Afficheur et la propage à tous les Afficheurs.
 *               Peut aussi être positionné par le calculateur.
 * \param newValeurPivot: Timecode en microsecondes.
 * \see signal Afficheur::setValuePivot()
 * \see signal Operande::valeurPivotChanged()
 * \see slot Afficheur::setValue()
 * ***********************************************************************************************************/
void Operande::setValeurPivot(const qint64 newValeurPivot, const bool force)
{
    if (newValeurPivot > this->mMaxValue)
    {
        qDebug("ERROR: msg_max_reached: discard candidate %d ! ", newValeurPivot);
    }
    else
    {
        qDebug() << mName << "received new pivot (us)" << newValeurPivot << force;
        mValeurPivot = newValeurPivot;
        emit valeurPivotChanged(newValeurPivot, force);
    }
}

/*! **********************************************************************************************************
 * \brief SLOT : Vide la valeur pivot, et efface la valeur de tous les Afficheur.
 * \see Signal Afficheur::clearValue()
 * ***********************************************************************************************************/
void Operande::clearValeurPivot()
{
    qDebug()<< mName << "::clearValeurPivot";
    mValeurPivot = 0;
    emit valeurPivotCleared();
}

/*! **********************************************************************************************************
 * \brief Enregistre les afficheurs dans le contexte QML, pour pouvoir les afficher.
 * \note Les property names seront du type "tc1_aff_1"
 * \param context: Le rootContext de l'application.
 * ***********************************************************************************************************/
void Operande::registerContext(QQmlContext* context)
{
    context->setContextProperty(mName+"_aff_1", a1);
    context->setContextProperty(mName+"_aff_2", a2);
    context->setContextProperty(mName+"_aff_3", a3);
    context->setContextProperty(mName+"_aff_4", a4);
    context->setContextProperty(mName+"_aff_5", a5);  // D+HMSmm
    context->setContextProperty(mName+"_aff_6", a6);
    context->setContextProperty(mName+"_aff_7", a7);
    //context->setContextProperty(mName+"_aff_8", a8);
}

/*! **********************************************************************************************************
 * \brief Cree des connexions entre l'objet QML "afficheurActif" et tous les Afficheurs.
 *        Ainsi, lorsque l'afficheur actif change, tous les afficheurs sont informés.
 * \param context: Le root context de l'application.
 * ***********************************************************************************************************/
void Operande::connectActiveDisplay(QQmlApplicationEngine* engine)
{
    // On trove l'objet QML nommé "afficheurActif"
    QObject* qmlItem = engine->rootObjects().constFirst()->findChild<QObject*>("afficheurActif");
    // On le connecet à tous les afficheurs.
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a1, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a2, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a3, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a4, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a5, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a6, SLOT(activeDisplay(QString)));
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a7, SLOT(activeDisplay(QString)));
}
