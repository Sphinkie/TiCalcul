#ifndef OPERANDE_H
#define OPERANDE_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine.h>
#include "afficheur.h"


class Operande : public QObject
{
    Q_OBJECT

// ------------------------------------------------------------------------------------------
// Méthodes
// ------------------------------------------------------------------------------------------
public:
    explicit Operande(QString name, QObject* parent = nullptr);

    qint64 valeurPivot() const;
    void registerContext(QQmlContext* context);
    void setPartner(Operande* partner);

    Q_INVOKABLE void connectActiveDisplay(QQmlApplicationEngine* engine);
    Q_INVOKABLE void clearValeurPivot();

public slots:
    void setValeurPivot(const qint64 newValeurPivot, const bool force=false);

signals:
    void valeurPivotChanged(qint64, bool);   // Signal indiquant que la valeur pivot a été modifiée.
    void valeurPivotCleared();               // Signal indiquant que la valeur pivot a été effacée.

private:
    qint64 mValeurPivot = 0;                      // Valeur pivot en microsecondes
    const qint64 mMaxValue = 99'999'999'999'999;  // Valeur pivot maximale autorisée (99 999 999 999 999 microsecondes) soit environ 1000 jours.
                                                  // A noter que le uint32 est limité à 4.294.967.295. D'où l'utilisation du qint64 (long long)

    Afficheur* a1;         // Afficheur en secondes
    Afficheur* a2;         // Afficheur en millisecondes
    Afficheur* a3;         // Afficheur en microsecondes
    Afficheur* a4;         // Afficheur en HMSI
    Afficheur* a5;         // Afficheur en Day + HSMm
    Afficheur* a6;         // Afficheur en Frames (25 fps)
    Afficheur* a7;         // Afficheur en Frames (50 fps)
    Afficheur* a8;         // Afficheur en Frames (NTSC)
    QQmlContext* mContext;
	
};

#endif // OPERANDE_H
