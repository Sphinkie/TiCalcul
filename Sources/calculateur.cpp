#include "calculateur.h"


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
 /*!
 * \class Calculateur
 * \inmodule TiCalcul
 * \brief La classe Calculateur gère les opérations entre les opérandes: addition, soustraction, complément.
 *
 * \sa Operande
 **/




 /* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \fn Calculateur::Calculateur()
 * \brief Constructeur. Les paramètres sont des \l Operande.
 *
 * \a tc1: premier opérande. \br
 * \a tc2: second opérande. \br
 * \a result: opérande résultat. \br
 * \a parent: QObject parent. \br
 **/
Calculateur::Calculateur(Operande* tc1, Operande* tc2, Operande* result, QObject* parent)
{
    this->mTC1 = tc1;
    this->mTC2 = tc2;
    this->mResult = result;
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Calcule le complément à 24H de TC1 et envoie le résultat à l'opérande Result.
 **/
void Calculateur::complement()
{
    qint64 value = mTC1->valeurPivot();
    // la valeur doit être positive et inférieure à 24h.
    if ((value < 0) || (value > Converter::us_PerDay))
        mResult->clearValeurPivot();
    else
        mResult->setValeurPivot(Converter::us_PerDay - value);
    mOperation = complt;
    mOperateur = "Cmplt";
    emit operateurChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Calcule la somme TC1+TC2 et envoie le résultat à l'opérande Result.
 **/
void Calculateur::add()
{
    qint64 somme = mTC1->valeurPivot() + mTC2->valeurPivot();
    mResult->setValeurPivot(somme);
    mOperation = addition;
    mOperateur = "+";
    emit operateurChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Calcule la différence TC1-TC2 et envoie le résultat à l'opérande Result.
 **/
void Calculateur::substract()
{
    qint64 result = mTC1->valeurPivot() - mTC2->valeurPivot();
    mResult->setValeurPivot(result);
    mOperation = soustraction;
    mOperateur = "-";
    emit operateurChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Echange la valeur des opérandes TC1 et TC2.
 **/
void Calculateur::swap()
{
    qint64 temp_1 = mTC1->valeurPivot();
    qint64 temp_2 = mTC2->valeurPivot();
    mTC1->setValeurPivot(temp_2, true);
    mTC2->setValeurPivot(temp_1, true);
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Recopie la valeur du résultat dans l'opérande TC1.
 **/
void Calculateur::memorize()
{
    qint64 temp_1 = mResult->valeurPivot();
    mTC1->setValeurPivot(temp_1, true);
    mOperation = none;
    mOperateur = "";
    emit operateurChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Efface l'opérateur en cours.
 **/
void Calculateur::clear()
{
    mOperation = none;
    mOperateur = "";
    emit operateurChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \fn void Calculateur::onValeurPivotChanged()
 * \brief Si la valeur de l'un des opérandes à changé, on actualise le resultat.
 **/
void Calculateur::onValeurPivotChanged()
{
    switch (mOperation) {
    case addition:
        this->add();
        break;
    case soustraction:
        this->substract();
        break;
    case complt:
        this->complement();
        break;
    default:
        break;
    }
}
