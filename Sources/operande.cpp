#include "operande.h"

#include <QQmlEngine>

/*! **********************************************************************************************************
 * \brief Constructeur: crée les 8 afficheurs de cet opérande, et les connecte pour leur envoyer un signal
 *        à chaque modification de la valeur pivot.
 * \note L'afficheur NTSC est désactivé pour le moment.
 * \param name: Le nom de l'operande: "TC1" ou "TC2" ou eRESULT".
 * \param parent: Paramètre classique pour les QObject.
 * ***********************************************************************************************************/
Operande::Operande(const QString name, QObject *parent)
{
    this->mName = name;

    a1 = new Afficheur(Unites::SECONDS, name);
    a2 = new Afficheur(Unites::MILLISECONDS, name);
    a3 = new Afficheur(Unites::MICROSECONDS, name);
    a4 = new Afficheur(Unites::HMSI, name);
    a5 = new Afficheur(Unites::DHMSM, name);
    a6 = new Afficheur(Unites::FRAMES_25, name);
    a7 = new Afficheur(Unites::FRAMES_50, name);
    //a8 = new Afficheur(Unites::FRAMES_NTSC);

    QList<Afficheur*> afficheurs = {a1, a2, a3, a3, a4, a5, a6, a7};
    QList<Afficheur*>::iterator it;

    for (it=afficheurs.begin(); it != afficheurs.end();  it++)
    {
        // Connexions: Envoi de la valeur pivot aux afficheurs.
        QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), *it, SLOT(setValue(qint64)));
        // Connexions: Signale aux afficheurs que la valeur pivot a été effacée.
        QObject::connect(this, SIGNAL(valeurPivotCleared()), *it, SLOT(clearValue()));
        // Connexions: Réception des modifications de la valeur pivot.
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
 * \brief SLOT : Reçoit et propage la nouvelle valeur pivot aux afficheurs.
 * \param newValeurPivot: Timecode en microsecondes.
 * \see Afficheur::setValue()
 * TODO remplacer le qint64 en quint64
 * ***********************************************************************************************************/
void Operande::setValeurPivot(const qint64 newValeurPivot)
{
    if (newValeurPivot > this->mMaxValue)
    {
        qDebug("ERROR: msg_max_reached: discard candidate %d ! ", newValeurPivot);
    }
    else if (mValeurPivot != newValeurPivot)
    {
        qDebug("received new pivot: %d us", newValeurPivot);
        mValeurPivot = newValeurPivot;
        emit valeurPivotChanged(newValeurPivot);
    }
}

/*! **********************************************************************************************************
 * \brief SLOT : Vide la valeur pivot, et efface la valeur de tous les afficheurs.
 * ***********************************************************************************************************/
void Operande::clearValeurPivot()
{
    qDebug("clear valeur Pivot");
    mValeurPivot = 0;
    emit valeurPivotCleared();
}

/*! **********************************************************************************************************
 * \brief Enregistre les afficheurs dans le contexte QML, pour pouvoir les afficher.
 * \param context: Le root context de l'application.
 * ***********************************************************************************************************/
void Operande::registerContext(QQmlContext* context)
{
    context->setContextProperty(mName+"_aff_1", a1);
    context->setContextProperty(mName+"_aff_2", a2);
    context->setContextProperty(mName+"_aff_3", a3);
    context->setContextProperty(mName+"_aff_4", a4);
    context->setContextProperty(mName+"_aff_5", a5);
    context->setContextProperty(mName+"_aff_6", a6);
    context->setContextProperty(mName+"_aff_7", a7);
    //context->setContextProperty(mName+"_aff_8", a8);
    //qDebug() << context->metaObject()->propertyCount();  // renvoie 1
    //qDebug() << context->dynamicPropertyNames();         // renvoie la liste des setProperty, donc ici: liste vide
    //qDebug() << context->objectName();                   // vide car non défini explicitement
    //qDebug() << context->contextProperty("TC2_aff_4");   // trouvé, car défini avec setContextProperty()

    mContext = context;
}

/*! **********************************************************************************************************
 * \brief Cree des connexions entre l'objet QML "afficheurActif" et tous les Afficheurs.
 *        Ainsi, lorsque l'afficheur actif change, tous les afficheurs sont informés.
 * \param context: Le root context de l'application.
 * ***********************************************************************************************************/
void Operande::connectActiveDisplay(QQmlApplicationEngine* engine)
{
   QQmlContext* context = mContext;

    qDebug() << "connectActiveDisplay -- context";
    qDebug() << context->objectForName("afficheurActif");
    qDebug() << context->metaObject()->propertyCount();             // renvoie 1
    qDebug() << context->dynamicPropertyNames();                    // renvoie la liste des setProperty, donc ici: liste vide
    qDebug() << context->contextProperty("afficheurActif");         // vide - QVariant(Invalid)
    qDebug() << context->contextProperty("TC2_aff_4");              // trouvé

     qDebug() << "connectActiveDisplay -- engine";
     qDebug() << engine->property("afficheurActif");                // vide - QVariant(Invalid)
     qDebug() << engine->dynamicPropertyNames();                    // QList("_q_QQuickUniversalStyle")
     qDebug() << engine->rootObjects();                             // QList(Main_QMLTYPE_18)
     qDebug() << engine->rootObjects().first();
     qDebug() << engine->rootObjects().first()->children();         // QList(QQuickRootItem(0x25065539b60), QQuickRectangle(0x2506557d560,name = "pagePrincipale"), QQuickUniversalStyle(0x250658a9830))
     qDebug() << engine->rootObjects().first()->objectName();                // vide
     qDebug() << engine->rootObjects().first()->dynamicPropertyNames();      // vide
     qDebug() << engine->rootObjects().first()->property("window");          //  QVariant(Invalid)
     qDebug() << engine->rootObjects().first()->property("pagePrincipale");  //  QVariant(Invalid)
     qDebug() << engine->rootObjects().first()->property("afficheurActif");  // QVariant(Invalid)
     qDebug() << engine->rootObjects().first()->children()[1]->objectName(); // "pagePrincipale"
     qDebug() << engine->rootObjects().first()->children()[1]->children();   // QList(ActiveDisplay_QMLTYPE_1(0x201aeaebe10, name = "afficheurActif"), QQuickGridLayout(0x201ae9434a0), QQuickUniversalStyle(0x201aed5e920))
     //qDebug() << view.rootObject();
     qDebug() << engine->rootObjects().first()->findChild<QObject*>("afficheurActif");  // ActiveDisplay_QMLTYPE_17(0x23acd5f0780, name = "afficheurActif")
     qDebug() << engine->rootObjects().first()->findChildren<QObject*>("afficheurActif");  //QList(ActiveDisplay_QMLTYPE_17(0x23acd5f0780, name = "afficheurActif"))

     QObject* qmlItem;
    // qmlItem = engine->rootObjects().constFirst()->findChild<QObject*>("afficheurActif");
    qmlItem = engine->rootObjects().first();
    QObject::connect(qmlItem, SIGNAL(activeDisplay(QString)), a1, SLOT(activeDisplay(QString)));
}
