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
    Q_PROPERTY(Operation operation MEMBER mOperation NOTIFY operationChanged)
    Q_PROPERTY(QString operat MEMBER mOperateur NOTIFY operatChanged)

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
    void operationChanged();
    void operatChanged();

public:
    enum Operation {none, addition, soustraction, complt};
    Q_ENUM(Operation)
    Operation mOperation = none;  //!< opération en cours
    QString mOperateur = "none";  //!< opération en cours

private:
    Operande* mTC1;         //!< premier opérande.
    Operande* mTC2;         //!< second opérande.
    Operande* mResult;      //!< opérande résultat.
};

#endif // CALCULATEUR_H
