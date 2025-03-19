#ifndef CALCULATEUR_H
#define CALCULATEUR_H

#include <QObject>

#include "Operande.h"

/*! **********************************************************************************************************
 * \brief La classe Calculateur est en charge de gérer les opérations entre
 * les opérandes: addition, soustraction, complément.
 ************************************************************************************************************* */

class Calculateur : public QObject
{
    Q_OBJECT

public:
    explicit Calculateur(Operande* tc1, Operande* tc2, Operande* result, QObject* parent = nullptr);
    Q_INVOKABLE void complement();
    Q_INVOKABLE void add();
    Q_INVOKABLE void substract();
    Q_INVOKABLE void swap();

signals:


private:
    Operande* mTC1;         //!< premier opérande.
    Operande* mTC2;         //!< second opérande.
    Operande* mResult;      //!< opérande résultat.
};

#endif // CALCULATEUR_H
