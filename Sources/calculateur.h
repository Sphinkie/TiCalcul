#ifndef CALCULATEUR_H
#define CALCULATEUR_H

#include <QObject>

#include "Operande.h"


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
    Q_INVOKABLE void clear();

public slots:
    void onValeurPivotChanged();

signals:
    void operateurChanged();

public:
    QString mOperateur = "";      // Opération en cours (string affichable)

private:
    Operande* mTC1;               // Premier opérande.
    Operande* mTC2;               // Second opérande.
    Operande* mResult;            // Opérande résultat.
    enum Operation {none, addition, soustraction, complt};
    Operation mOperation = none;  // Opération en cours
};

#endif // CALCULATEUR_H
