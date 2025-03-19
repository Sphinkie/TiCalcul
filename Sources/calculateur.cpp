#include "calculateur.h"


/*! **********************************************************************************************************
 * \brief Constructeur.
 * \param tc1: premier opérande.
 * \param tc2: second opérande.
 * \param result: opérande résultat.
 * \param parent: QObject parent.
 ************************************************************************************************************* */
Calculateur::Calculateur(Operande* tc1, Operande* tc2, Operande* result, QObject* parent)
{
    this->mTC1 = tc1;
    this->mTC2 = tc2;
    this->mResult = result;
}

/*! **********************************************************************************************************
 * \brief Calculateur::complement
 ************************************************************************************************************* */
void Calculateur::complement()
{
    qint64 value = mTC1->valeurPivot();
    // la valeur doit être positive et inférieure à 24h.
    if (value > Converter::us_PerDay) return;
    if (value < 0) return;
    mResult->setValeurPivot(Converter::us_PerDay - value);
}

/*! **********************************************************************************************************
 * \brief Calculateur::add
 ************************************************************************************************************* */
void Calculateur::add()
{
    qint64 somme = mTC1->valeurPivot() + mTC2->valeurPivot();
    mResult->setValeurPivot(somme);
}

/*! **********************************************************************************************************
 * \brief Calculateur::substract
 ************************************************************************************************************* */
void Calculateur::substract()
{
    qint64 result = mTC1->valeurPivot() - mTC2->valeurPivot();
    mResult->setValeurPivot(result);
}

/*! **********************************************************************************************************
 * \brief Calculateur::swap
 ************************************************************************************************************* */
void Calculateur::swap()
{
    qint64 temp_1 = mTC1->valeurPivot();
    qint64 temp_2 = mTC2->valeurPivot();
    mTC1->setValeurPivot(temp_2);
    mTC2->setValeurPivot(temp_1);
}
