#ifndef CALCULATEUR_H
#define CALCULATEUR_H

#include <QObject>

#include "Operande.h"

/*! **********************************************************************************************************
 * \class Calculateur
 * \brief La classe Calculateur est en charge de gérer les opérations entre les opérandes:
 *        addition, soustraction, complément.
 *************************************************************************************************************/

class Calculateur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString operateur MEMBER mOperateur NOTIFY operateurChanged)

public:
    explicit Calculateur(Operande* tc1, Operande* tc2, Operande* result, QObject* parent = nullptr);
    Q_INVOKABLE void complement();
    Q_INVOKABLE void add();
    Q_INVOKABLE void substract();
    Q_INVOKABLE void swap();
    Q_INVOKABLE void memorize();

public slots:
    void onValeurPivotChanged();

signals:
    void operateurChanged();

public:
    QString mOperateur = "";  //!< opération en cours (string affichable)

private:
    Operande* mTC1;         //!< premier opérande.
    Operande* mTC2;         //!< second opérande.
    Operande* mResult;      //!< opérande résultat.
    enum Operation {none, addition, soustraction, complt};
    Operation mOperation = none;  //!< opération en cours
};

#endif // CALCULATEUR_H
