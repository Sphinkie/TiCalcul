#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayValue MEMBER mDisplayValue NOTIFY displayValueChanged)

// ------------------------------------------------------------
// Méthodes
// ------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QObject *parent = nullptr);

    Q_INVOKABLE void setFrameRate(double framerate);

    QString displayValue() const;
    QString getName();
    double getFrameRate();
    int length();

public slots:
    void setValue(qint64 value);

signals:
    void displayValueChanged(QString);

protected:
    void setDisplayValue(QString value);
    void clearDisplayValue();
    qint32 _addDigit(QString digit);
    qint32 _removeLastDigit();
    bool isIncorrect(QString rawHmsi);

// ------------------------------------------------------------
// Variables membres
// ------------------------------------------------------------
private:
    QString mDisplayValue;      //!< La valeur à afficher (String)
    QString mName;              //!< Le nom de l'unité utilisée par cet afficheur
    Unites::Units mUnit;        //!< Unité utilisée par cet afficheur
    long mMaxValue;             //!< Valeur numérique maximale autorisée
    int mDecimals;              //!< Nombre de chiffres après la virgule
    double mFrameRate;          //!< Framerate utilisé (pour les afficheurs FRAMES et HMSI)
    double mConversionFacteur;  //!< Nombre de microseconds par unité

};

#endif // AFFICHEUR_H
