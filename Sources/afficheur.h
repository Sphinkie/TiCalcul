#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur
{
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
    Afficheur(Unites unit);
    void setFrameRate(double framerate);
    QString getStringValue();
    double getFrameRate();
    int length();
    QString name();

protected:
    long _addDigit(QString digit);
    long _removeLastDigit();
    void clear();
    bool isIncorrect(QString rawHmsi);

};

#endif // AFFICHEUR_H
