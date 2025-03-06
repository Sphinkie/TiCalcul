// #include <QQmlApplicationEngine>
// #include <QQmlContext>
#include "operande.h"

Operande::Operande(QString name, QObject *parent)
{
    this->mName = name;

    a1 = new Afficheur(Unites::SECONDS);
    a2 = new Afficheur(Unites::MILLISECONDS);
    a3 = new Afficheur(Unites::MICROSECONDS);
    a4 = new Afficheur(Unites::HMSI);
    a5 = new Afficheur(Unites::DHMSM);

    // Connexions
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a1, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a2, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a3, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a4, SLOT(setValue(qint64)));
    QObject::connect(this, SIGNAL(valeurPivotChanged(qint64)), a5, SLOT(setValue(qint64)));

}

qint64 Operande::valeurPivot() const
{
    return mValeurPivot;
}

/*! ********************************************************************************************
 * \brief Reçoit et propage la nouvelle valeur pivot aux afficheurs.
 * \param newValeurPivot Timecode en microsecondes.
 */
void Operande::setValeurPivot(qint64 newValeurPivot)
{
    mValeurPivot = newValeurPivot;
    emit valeurPivotChanged(mValeurPivot);
}

/*! ********************************************************************************************
 * \brief Enregistre les afficheurs dans le contexte QML, pour pouvoir les afficher.
 * \param context Le root context de l'application.
 */
void Operande::registerContext(QQmlContext* context)
{
    context->setContextProperty(mName+"aff_1", a1);
    context->setContextProperty(mName+"aff_2", a2);
    context->setContextProperty(mName+"aff_3", a3);
    context->setContextProperty(mName+"aff_4", a4);
    context->setContextProperty(mName+"aff_5", a5);
}


