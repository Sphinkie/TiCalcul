#ifndef OPERANDE_H
#define OPERANDE_H

#include <QObject>
#include <QQmlContext>
#include "afficheur.h"


/* ********************************************************************************************************** */
/*!
 * \class Operande
 * \brief La class Operande gère la "valeur pivot" (cad en microsecondes) de l'opérande TC1 ou de TC2.
 */
/* ********************************************************************************************************** */
class Operande : public QObject
{
    Q_OBJECT

public:
    Operande(QString name, QObject *parent = nullptr);

    qint64 valeurPivot() const;
    void setValeurPivot(qint64 newValeurPivot);
    void registerContext(QQmlContext* context);
    Q_INVOKABLE void clear();

signals:
    void valeurPivotChanged(qint64);

private:
    qint64 mValeurPivot;  //!< Valeur pivot en microsecondes
    QString mName;        //!< Vaut TC1 ou TC2

    Afficheur* a1;        //!< Afficheur en secondes
    Afficheur* a2;        //!< Afficheur en millisecondes
    Afficheur* a3;        //!< Afficheur en microsecondes
    Afficheur* a4;        //!< Afficheur en HMSI
    Afficheur* a5;        //!< Afficheur en Day + HSMm
    Afficheur* a6;        //!< Afficheur en Frames (25 fps)
    Afficheur* a7;        //!< Afficheur en Frames (50 fps)
    Afficheur* a8;        //!< Afficheur en Frames (NTSC)
};

#endif // OPERANDE_H
