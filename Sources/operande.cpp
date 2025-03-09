#include "operande.h"


/* ********************************************************************************************************** */
/*!
 * \brief Constructeur: crée les 8 afficheurs de cet opérande, et les connecte pour leur envoyer un signal
 *        à chaque modification de la valeur pivot.
 * \note L'afficheur NTSC est désactivé pour le moment.
 * \param name: Le nom de l'operande: "TC1" ou "TC2".
 * \param parent: Paramètre classique pour les QObject.
 */
Operande::Operande(QString name, QObject *parent)
{
    this->mName = name;

    a1 = new Afficheur(Unites::SECONDS);
    a2 = new Afficheur(Unites::MILLISECONDS);
    a3 = new Afficheur(Unites::MICROSECONDS);
    a4 = new Afficheur(Unites::HMSI);
    a5 = new Afficheur(Unites::DHMSM);
    a6 = new Afficheur(Unites::FRAMES_25);
    a7 = new Afficheur(Unites::FRAMES_50);
    //a8 = new Afficheur(Unites::FRAMES_NTSC);

    // Connexions: Envoi de la valeur pivot aux afficheurs.
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a1, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a2, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a3, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a4, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a5, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a6, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a7, SLOT(setValue(qint64)));
    //QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a8, SLOT(setValue(qint64)));
    // Connexions: Réception des modifications de la valeur pivot.
    QObject::connect(a1, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a2, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a3, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a4, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a5, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a6, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    QObject::connect(a7, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));
    //QObject::connect(a8, SIGNAL(setValeurPivot(qint64)), this, SLOT(setValeurPivot(qint64)));

}

/* ********************************************************************************************************** */
 /*!
 * \brief Renvoie la valeur Pivot (en microsecondes).
 * \returns the value in microseconds.
 */
qint64 Operande::valeurPivot() const
{
    return mValeurPivot;
}

/* ********************************************************************************************************** */
 /*!
 * \brief Reçoit et propage la nouvelle valeur pivot aux afficheurs.
 * \param newValeurPivot: Timecode en microsecondes.
 */
void Operande::setValeurPivot(qint64 newValeurPivot)
{
    mValeurPivot = newValeurPivot;
    emit valeurPivotChanged(mValeurPivot);
}

/* ********************************************************************************************************** */
/*!
 * \brief Vide la valeur pivot.
 * \todo Mettre une valeur NULL
 */
void Operande::clear()
{
    setValeurPivot(0);
}

/* ********************************************************************************************************** */
/*!
 * \brief Enregistre les afficheurs dans le contexte QML, pour pouvoir les afficher.
 * \param context: Le root context de l'application.
 */
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
}


