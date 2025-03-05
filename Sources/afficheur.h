#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "unites.h"
#include <QObject>

class Afficheur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value MEMBER mValue NOTIFY valueChanged)

    // ------------------------------------------------------------
    // Variables membres
    // ------------------------------------------------------------
private:
    QString mName;         // Le nom de l'afficheur
    long mMaxValue;        // Valeur maximale autorisée
    QString mValue;        // La valeur à afficher (String)
    Unites::Units mUnit;

protected:
    double mConversionFacteur; // Nombre de microseconds par unité
    int mDecimals;             // Nombre de chiffres après la virgule
    double mFrameRate;         // Framerate utilisé (pour les afficheurs FRAMES et HMSI)


    // ------------------------------------------------------------
    // Méthodes
    // ------------------------------------------------------------
public:
    explicit Afficheur(Unites::Units unit, QObject *parent = nullptr);
    void setFrameRate(double framerate);
    QString getStringValue();
    double getFrameRate();
    int length();
    QString name();

public slots:
    void setValue(qint64 value);

signals:
    void valueChanged(qint64);

protected:
    qint32 _addDigit(QString digit);
    qint32 _removeLastDigit();
    void clear();
    bool isIncorrect(QString rawHmsi);

};

#endif // AFFICHEUR_H
