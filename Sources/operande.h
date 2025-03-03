#ifndef OPERANDE_H
#define OPERANDE_H

#include <QObject>

class Operande : public QObject
{
    Q_OBJECT

public:
    Operande(QObject *parent = nullptr);

    qint64 valeurPivot() const;
    void setValeurPivot(qint64 newValeurPivot);

private:
    qint64 mValeurPivot;

signals:
    void valeurPivotChanged(qint64);
};

#endif // OPERANDE_H
