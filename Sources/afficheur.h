#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur : public QObject
{
    Q_OBJECT

// ------------------------------------------------------------
// variables membres
// ------------------------------------------------------------
private:
    QString mName;          // Le nom de l'afficheur
    long mMaxValue;        // Valeur maximale autorisée

protected:
    QString mStringValue;       // La valeur affichée (String)
    double mConversionFacteur; // Nombre de microseconds par unité
    int mDecimals;             // Nombre de chiffres après la virgule
    double mFrameRate;         // Framerate utilisé (pour les afficheurs FRAMES et HMSI)

public:
    explicit Afficheur(QObject *parent = nullptr, Unites::Units unit= Unites::HMSI);
    void setFrameRate(double framerate);
    QString getStringValue();
    double getFrameRate();
    int length();
    QString name();

protected:
    qint32 _addDigit(QString digit);
    qint32 _removeLastDigit();
    void clear();
    bool isIncorrect(QString rawHmsi);

};

#endif // AFFICHEUR_H
