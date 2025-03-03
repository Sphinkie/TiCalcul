#include "operande.h"
#include "afficheur.h"

Operande::Operande(QObject *parent)
{

    Afficheur a1(Unites::SECONDS);
    Afficheur a2(Unites::MILLISECONDS);

    // Connexions
    QObject::connect(this, SIGNAL(valeurPivotChanged()), &a1, SLOT(setValue()));
    QObject::connect(this, SIGNAL(valeurPivotChanged()), &a2, SLOT(setValue()));
}

qint64 Operande::valeurPivot() const
{
    return mValeurPivot;
}

void Operande::setValeurPivot(qint64 newValeurPivot)
{
    mValeurPivot = newValeurPivot;
    emit valeurPivotChanged(mValeurPivot);
}


