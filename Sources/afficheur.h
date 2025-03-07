#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayValue MEMBER mDisplayValue NOTIFY displayValueChanged)

    // ------------------------------------------------------------
    // Variables membres
    // ------------------------------------------------------------
private:
    QString mName;              //!< Le nom de l'afficheur
    Unites::Units mUnit;        //!< Unité utilisée par cet afficheur
    long mMaxValue;             //!< Valeur numérique maximale autorisée
    QString mDisplayValue;      //!< La valeur à afficher (String)

protected:
    int mDecimals;              //!< Nombre de chiffres après la virgule
    double mFrameRate;          //!< Framerate utilisé (pour les afficheurs FRAMES et HMSI)
    double mConversionFacteur;  //!< Nombre de microseconds par unité


    // ------------------------------------------------------------
    // Méthodes
    // ------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QObject *parent = nullptr);

    QString displayValue() const;
    QString getName();
    double getFrameRate();
    void setFrameRate(double framerate);
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

};

#endif // AFFICHEUR_H
