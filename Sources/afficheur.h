#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

/*! **********************************************************************************************************
 * \brief La classe Afficheur gère un champ numérique de l'IHM.
 *        Elle est associée à un objet QML FieldInput et lui envoie les valeurs à afficher.
 *        Il y a un Afficheur pour chaque unité: Secondes, Millisecondes, HMSI, etc.
 *************************************************************************************************************/

class Afficheur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayValue MEMBER mDisplayValue NOTIFY displayValueChanged)
    Q_PROPERTY(QString unit MEMBER mUnitName NOTIFY unitChanged)
    Q_PROPERTY(QString hint MEMBER mHint NOTIFY hintChanged)
    Q_PROPERTY(qreal framerate MEMBER mFramerate WRITE setFramerate NOTIFY framerateChanged)

// ------------------------------------------------------------
// Méthodes
// ------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QString parentName, QObject *parent = nullptr);

    Q_INVOKABLE void addDigit(QString digit);
    Q_INVOKABLE void removeLastDigit();
    Q_INVOKABLE void rectifyHMSI();

public slots:
    void setValue(const qint64 microsecs, const bool force=false);  //!< Réception du signal valeurPivotChanged
    void clearValue();
    void activeDisplay(QString afficheur);
    void setFramerate(double framerate);

signals:
    void displayValueChanged();         //!< Indique au QML que la valeur à afficher a changé.
    void framerateChanged();            //!< Indique au QML que le framerate de l'afficheur HMSI a changé.
    void setValeurPivot(qint64);        //!< Envoi à l'opérande d'une nouvelle valeur pivot.
    void unitChanged();                 //!< En fait, l'unité d'un afficheur ne change jamais.
    void hintChanged();                 //!< En fait, le hint d'un afficheur ne change jamais.

private:
    void setDisplayValue(const QString value, const bool force=false);
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
    double mFramerate;          //!< Framerate utilisé (pour les afficheurs FRAMES et HMSI)
    double mConversionFacteur;  //!< Nombre de microseconds par unité
    qint64 mMaxValue;           //!< Valeur maximale supportée par cette unité (sauf HMSI)
};

#endif // AFFICHEUR_H
