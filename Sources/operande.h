#ifndef OPERANDE_H
#define OPERANDE_H

#include <QObject>
#include <QQmlContext>
#include "afficheur.h"


class Operande : public QObject
{
    Q_OBJECT

public:
    Operande(QString name, QObject *parent = nullptr);

    qint64 valeurPivot() const;
    void setValeurPivot(qint64 newValeurPivot);
    void registerContext(QQmlContext* context);

signals:
    void valeurPivotChanged(qint64);

private:
    qint64 mValeurPivot;
    QString mName;

    Afficheur* a1;
    Afficheur* a2;
    Afficheur* a3;
    Afficheur* a4;
    Afficheur* a5;

};

#endif // OPERANDE_H
