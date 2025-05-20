#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <QObject>
#include "unites.h"

class Afficheur : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString displayValue MEMBER mDisplayValue NOTIFY displayValueChanged)
    Q_PROPERTY(qreal framerate MEMBER mFramerate WRITE setFramerate NOTIFY framerateChanged)
    Q_PROPERTY(QString unit MEMBER mUnitName NOTIFY unitChanged)
    Q_PROPERTY(QString hint MEMBER mHint NOTIFY hintChanged)
    Q_PROPERTY(bool correct MEMBER mCorrect NOTIFY correctChanged)
    Q_PROPERTY(const Afficheur* partner MEMBER mPartner NOTIFY partnerChanged)
    Q_PROPERTY(const Afficheur* up MEMBER mUp)
    Q_PROPERTY(const Afficheur* down MEMBER mDown)
    Q_PROPERTY(const Afficheur* right MEMBER mRight)
    Q_PROPERTY(const Afficheur* left MEMBER mLeft)
    Q_PROPERTY(const QObject* parent MEMBER mParent)

// ------------------------------------------------------------------------------------------
// Méthodes
// ------------------------------------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QObject *parent = nullptr);
    void findPartner(QString partnername);
    void setNavigation(Afficheur* N, Afficheur* S, Afficheur* E, Afficheur* W);

    Q_INVOKABLE void addDigit(QString digit);
    Q_INVOKABLE void removeLastDigit();
    Q_INVOKABLE void rectifyHMSI();
    Q_INVOKABLE void paste(QString value);
    Q_INVOKABLE QString copy();

public slots:
    void setValue(const qint64 microsecs, const bool force=false);  // Réception du signal valeurPivotChanged()
    void clearValue();                                              // Réception du signal valeurPivotCleared()
    void activeDisplay(QString afficheur);          // Réception du nom de l'afficheur actif, en cas de changement. QML.
    void setFramerate(double new_framerate);        // Réception d'une nouvelle valeur de framerate. Concerne le HMSI. QML.

signals:
    void displayValueChanged();         // Indique au QML que la valeur à afficher a changé.
    void framerateChanged();            // Indique au QML que le framerate de l'afficheur HMSI a changé.
    void setValeurPivot(qint64);        // Envoi à l'opérande d'une nouvelle valeur pivot.
    void unitChanged();                 // En fait, l'unité d'un afficheur ne change jamais.
    void hintChanged();                 // En fait, le hint d'un afficheur ne change jamais.
    void correctChanged();              // Indique que l'afficheur (HMSI) est devenu incorrect (ou correct).
    void partnerChanged();              // En fait, le partenaire d'un afficheur ne change jamais.

private:
    void setDisplayValue(const QString value, const bool force=false);
    bool isCorrect(const QString rawHmsi);

// ------------------------------------------------------------------------------------------
// Variables membres
// ------------------------------------------------------------------------------------------
private:
    QString mDisplayValue;      // QML Property: La valeur à afficher (String)
    QString mUnitName;          // QML Property: Le nom de l'unité utilisée par cet afficheur
    QString mHint;              // QML Property: Le texte à afficher si mDisplayValue est vide.
    double mFramerate;          // QML Property: Framerate utilisé (pour les afficheurs HMSI)
    bool mCorrect;              // QML Property: False si le format du HMSI est incorrect.
    const Afficheur* mPartner;        // QML Property: L'afficheur équivalent de l'autre opérande.
    const Afficheur* mUp;             // QML Property: Afficheur N situé au dessus.
    const Afficheur* mDown;           // QML Property: Afficheur S situé au dessous.
    const Afficheur* mRight;          // QML Property: Afficheur E situé à droite.
    const Afficheur* mLeft;           // QML Property: Afficheur W situé à Gauche.
    const QObject* mParent;           // QML Property: Operande parent.

    bool mIsActive = false;     // Indique si cet afficheur est en cours d'édition. Positionné par le QML.

    QString mRawHMSI;           // utilisé par les afficheurs HMSI
    QString mRawNUM;            // utilisé par les afficheurs Numériques
    Unites::Units mUnit;        // Unité utilisée par cet afficheur
    double mConversionFacteur;  // Nombre de microseconds par unité
    qint64 mMaxValue;           // Valeur maximale supportée par cette unité (sauf HMSI)
};

#endif // AFFICHEUR_H
