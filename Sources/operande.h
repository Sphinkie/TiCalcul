#ifndef OPERANDE_H
#define OPERANDE_H

#include <QObject>
#include <QQmlContext>
#include "afficheur.h"


class Operande : public QObject
{
    Q_OBJECT

public:
    Operande(QObject *parent = nullptr);

    qint64 valeurPivot() const;
    void setValeurPivot(qint64 newValeurPivot);
    void registerContext(QQmlContext* context);

signals:
    void valeurPivotChanged(qint64);

private:
    qint64 mValeurPivot;

    Afficheur* a1;
    Afficheur* a2;
    Afficheur* a3;
};

#endif // OPERANDE_H
