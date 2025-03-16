#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayValue MEMBER mDisplayValue NOTIFY displayValueChanged)
    Q_PROPERTY(QString unit MEMBER mUnitName NOTIFY unitChanged)
    Q_PROPERTY(QString hint MEMBER mHint NOTIFY hintChanged)

// ------------------------------------------------------------
// Méthodes
// ------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QString parentName, QObject *parent = nullptr);

    Q_INVOKABLE void setFrameRate(double framerate);
    Q_INVOKABLE double getFrameRate() const;
    Q_INVOKABLE void addDigit(QString digit);
    Q_INVOKABLE void removeLastDigit();

public slots:
    void setValue(const qint64 microsecs);
    void clearValue();
    void activeDisplay(QString afficheur);

signals:
    void displayValueChanged();         //!< Indique au QML que la valeur à afficher a changé.
    void setValeurPivot(qint64);        //!< Envoi à l'opérande d'une nouvelle valeur pivot.
    void unitChanged();                 //!< En fait, l'unité d'un afficheur ne change jamais.
    void hintChanged();                 //!< En fait, le hint d'un afficheur ne change jamais.

private:
    void setDisplayValue(const QString value);
    bool isIncorrect(const QString rawHmsi);

// ------------------------------------------------------------
// Variables membres
// ------------------------------------------------------------
private:
    QString mDisplayValue;      //!< QML Property: La valeur à afficher (String)
    QString mUnitName;          //!< QML Property: Le nom de l'unité utilisée par cet afficheur
    QString mHint;              //!< QML Property: Le texte à afficher si mDisplayValue est vide.

    bool mIsActive = false;     //!< Indique si cet afficheur est en cours d'edition. Positionné par le QML.

    QString mRawHMSI;           //!< utilisé par les afficheurs HMSI
    QString mRawNUM;            //!< utilisé par les afficheurs Numériques
    Unites::Units mUnit;        //!< Unité utilisée par cet afficheur
    int mDecimals;              //!< Nombre de chiffres après la virgule
    double mFrameRate;          //!< Framerate utilisé (pour les afficheurs FRAMES et HMSI)
    double mConversionFacteur;  //!< Nombre de microseconds par unité

};

#endif // AFFICHEUR_H
