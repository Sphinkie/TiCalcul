#include "converter.h"
#include <qdebug.h>


/*!
 * \class Converter
 * \inmodule TiCalcul
 * \title Convertisseur d'unités
 *
 * \brief La classe Converter propose des fonctions de conversion de timecodes.
 *
 * La classe Converter est une classe statique contenant des fonctions de conversion de timecodes.
 */


/* ********************************************************************************************************** */
/*!
 * \brief Constructeur.
 */
Converter::Converter()
{
    // On initialise le NTSC à 30 fps.
    // NtscFramePerSec = 30.0;    // 30 ou 29.97 images par seconde
    // us_PerFrameNTSC = us_PerSecond / NtscFramePerSec;
}


/* ********************************************************************************************************** */
/*!
 * \brief Convertit un HMSI (même incomplet) en un nombre de micro-secondes.
 *
 * This function returns the value converted in microseconds. \br
 * \b Exemple:  "02:45:00:.." pour 2h45m en 9900000000 us.
 *
 * \a hmsi: HMSI string to convert. \br
 * \a framerate: le framerate utilisé dans le hmsi.
 */
qint64 Converter::HMSItoMicroseconds(QString hmsi, double framerate)
{
    QString rawHMSI = HMSItoRawHMSI(hmsi);
    qint64 microsecs = rawHMSItoMicroseconds(rawHMSI, framerate);
    return microsecs;
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Convertit un HMSI en un RAW HMSI (Exemple: "25:48:12:..' en "254812").
 *
 * Returns the corresponding RAW HMSI.
 *
 * \a hmsi: une string HMSI avec des ":" et des "..".
 */
QString Converter::HMSItoRawHMSI(QString hmsi)
{
    return hmsi.remove(':').remove('.');
}


/* ********************************************************************************************************** */
/*!
 * \brief Convertit un Raw HMSI (même partiel) en un nombre de micro-secondes.
 *
 * Returns the value converted in microseconds. \br
 * \b Exemple:  "0245" pour 2h45m = 9 900 000 000 us.
 *
 * \a raw_hmsi: raw hmsi to convert. \br
 * \a framerate: the framerate used for raw hmsi. \br
 */
qint64 Converter::rawHMSItoMicroseconds(QString raw_hmsi, double framerate)
{
    qint64 microsecs;
    QString hmsi_num = raw_hmsi.leftJustified(8,'0');   // on complete avec des "0"
    qDebug(qPrintable("filled RawHMSI: " + hmsi_num));
    microsecs = hmsi_num.left(2).toInt() * us_PerHour;                  // [0..1] hours
    microsecs += hmsi_num.mid(2, 2).toInt() * us_PerMinute;             // [2..3] minutes
    microsecs += hmsi_num.mid(4, 2).toInt() * us_PerSecond;             // [4..5] seconds
    microsecs += hmsi_num.mid(6, 2).toInt() * (us_PerSecond/framerate); // [6..7] frames
    return microsecs;
}


/* ********************************************************************************************************** */
/*!
 * \brief Ajoute des séparateurs de milliers sur la partie entière et la partie décimale.
 *
 * Returns a readable string with space separators.
 *
 * \a value: a numeric value.
 */
QString Converter::addSpaceSeparator(QString value)
{
    // 12 345.678 9
    QString formattedValue;
    int nbDigits = value.length();
    if (nbDigits == 0) return "0";
    int pointPos = value.indexOf('.');
    int lastUnit;
    // ----------------------------------------------------
    // Partie entière: 12 345
    // ----------------------------------------------------
    bool nombreEntier = (pointPos==-1);
    if (nombreEntier) lastUnit = nbDigits-1;
    else lastUnit = pointPos-1;
    // La partie entière va de 0 à lastUnit
    for (int i = lastUnit; i >= 0; i--)
    {
        // formattedValue = value.charAt(i) + formattedValue;
        // on ajoute au début
        formattedValue.insert(0, value.at(i));
        if ((lastUnit - i+1) % 3 == 0)
            formattedValue.insert(0, " ");
    }
    // ----------------------------------------------------
    // Cas où il n'y a pas de Partie décimale:
    // ----------------------------------------------------
    if (nombreEntier) return formattedValue;
    // ----------------------------------------------------
    // Cas avec Partie décimale: .678 9
    // ----------------------------------------------------
    formattedValue.append(".");
    // La partie décimale va de pointPos+1 à nbDigits-1
    for (int i = pointPos+1; i <= nbDigits-1; i++)
    {
        // if ((i-pointPos+1) % 3 == 0) formattedValue = formattedValue + " ";
        formattedValue.append(value.at(i));
    }
    return formattedValue;
}


/* ********************************************************************************************************** */
/*!
 * \brief Transforme une valeur en une string de 3 chars.
 *
 * Complète avec des zéro, et ne garde que les 3 chiffres les plus significatifs.
 * Returns the value completed with 0s (string size 3 chars). \br
 * \b Exemples:  25 devient "025", 4512 devient "451".
 *
 * \a value: numeric value to complete.
 */
QString Converter::adjustLengthTo3(qint64 value)
{
    QString str_value = QString::number(value);
    switch (str_value.length())
    {
    case 0:
        return "000";
    case 1:
        return "00" + str_value;
    case 2:
        return "0" + str_value;
    default:
        // Transforme aussi 4512 en 451
        return str_value.left(3);
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief Transforme une valeur en une string de 2 chars. Transforme 5 en "05".
 *
 * Returns the value completed with 0s (string size 2 chars).
 *
 * \a value: numeric value to complete.
 */
QString Converter::adjustLengthTo2(qint64 value)
{
    QString str_value;
    str_value.setNum(value);
    if (str_value.length() == 1)
        return "0" + str_value;
    else
        return str_value;
}

/* ********************************************************************************************************** */
/*!
 * \brief Returns the hmsi formatted with : and dots.
 *
 * \b Exemple: Transforme "123" en "12:3.:..:..".
 *
 * \a raw_hmsi: raw hmsi to convert.
 */
QString Converter::completeRawHMSIWithDots(QString raw_hmsi)
{
    QString hmsi = "..:..:..:..";
    int len = raw_hmsi.length();
    if (len > 0)
        hmsi[0] = raw_hmsi.at(0);
    if (len > 1)
        hmsi[1] = raw_hmsi.at(1);
    if (len > 2)
        hmsi[3] = raw_hmsi.at(2);
    if (len > 3)
        hmsi[4] = raw_hmsi.at(3);
    if (len > 4)
        hmsi[6] = raw_hmsi.at(4);
    if (len > 5)
        hmsi[7] = raw_hmsi.at(5);
    if (len > 6)
        hmsi[9] = raw_hmsi.at(6);
    if (len > 7)
        hmsi[10] = raw_hmsi.at(7);
    return hmsi;
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Transforme 1'234'000'000 en "1234" and returns the value converted in seconds, as a string.
 *
 * \b Note: Autant que possible, on évite les divisions int/float qui introduisent des pertes de précision.
 *
 * \a microsecs: microsecs value to convert.
 */
QString Converter::microsecsToSeconds(qint64 microsecs)
{
    //qDebug() << "microsecsToSeconds" << microsecs;
    QString stringValue;
    stringValue.setNum(microsecs);

    if (microsecs < 1'000) return "0";
    if (microsecs < 1'000'000)
    {
        stringValue.chop(3);
        return ("0." + stringValue.rightJustified(3,'0') );
    }
    // Autres cas: (supérieur à 1 seconde)
    stringValue.chop(3);
    QString decimales = stringValue.last(3);
    if (decimales == "000") decimales = "";
    else decimales.prepend('.');
    stringValue.chop(3);
    return stringValue + decimales;
}


/* ********************************************************************************************************** */
/*!
 * \brief Convertit un nombre de microsecondes en un nombre de frames (selon un certains framerate)
 *
 * Returns the \a microsecs value converted in frames, as a string. \br
 * \b Exemple: 1'234'000'000 ms en 25 fps donne "30850" frames. \br
 * \b Exemple: 1'234'000'000 ms en 50 fps donne "61700" frames.
 *
 * \a microsecs: microsecs value to convert. \br
 * \a framerate: framerate to use for conversion (ex: 25.0). \br
 */
QString Converter::microsecsToFrames(qint64 microsecs, double framerate)
{
    // qDebug() << "microsecsToFrames" << microsecs;
    qint64 numericValue = microsecs / 1000;   // millisecondes
    numericValue *= framerate;                // milliframes
    if (numericValue < 1000) return "0";      // cas du 0 frames
    QString stringValue = QString::number(numericValue);
    return stringValue.chopped(3);            // frames (on enleve les 3 derniers chiffres: arrondi vers le bas)
}


/* ********************************************************************************************************** */
/*!
 * \brief Returns the value converted in milliseconds, as a string.
 *
 * \b Exemple: Transforme 1'234'000'000 en "1234000".
 *
 * \a microsecs : microsecs value to convert.
 */
QString Converter::microsecsToMillis(qint64 microsecs)
{
    if (microsecs < 1000) return "0";
    QString stringValue = QString::number(microsecs);
    stringValue.chop(3);
    return stringValue;
}


/* ********************************************************************************************************** */
/*!
 * \brief Transforme une valeur numérique en un texte (readable string).
 *
 * \b Example:  1'234'000'000 en "1234000000".
 *
 * \a microsecs : microsecs value to convert.
 */
QString Converter::microseconds(qint64 microsecs)
{
    return QString::number(microsecs);
}


/* ********************************************************************************************************** */
/*!
 * \brief Returns a readable HMSI value (HH:MM:SS:II).
 *
 * \b Exemple: Transforme 1'234'000'000 en "00:20:34:00".
 *
 * \a microsecs : microsecs value to convert. \br
 * \a framerate : the framerate to use for the 2 last digits. \br
 */
QString Converter::microsecsToHMSI(qint64 microsecs, double framerate)
{
    qint64 quotient;
    qint64 reste;
    QString hmsi = "";
    if (microsecs == 0) return "00:00:00:00";
    if (microsecs < 0) {
        hmsi += "-";
        microsecs = abs(microsecs);
    }
    quotient = microsecs / us_PerHour;
    reste = microsecs % us_PerHour;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ":";

    quotient = reste / us_PerMinute;
    reste = reste % us_PerMinute;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ":";

    quotient = reste / us_PerSecond;
    reste = reste % us_PerSecond;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ":";

    // quotient = reste / us_PerFrame;
    quotient = (qint64)ceil(reste / 1'000'000.0 * framerate);
    hmsi += adjustLengthTo2(quotient);
    return hmsi;
}


/* ********************************************************************************************************** */
/*!
 * \brief Returns a readable HMSm value (HH:MM:SS,mmm).
 *
 * \b Exemple: Transforme 1'234'000'000 en "00:20:34,000".
 *
 * \a microsecs : microsecs value to convert.
 */
QString Converter::microsecsToHMSM(qint64 microsecs)
{
    qint64 quotient;
    qint64 reste;
    QString hmsi = "";
    // qDebug() << "microsecsToHMSM()" << microsecs;
    if (microsecs == 0) return "00:00:00,000";
    if (microsecs < 0) {
        hmsi += "-";
        microsecs = abs(microsecs);
    }
    quotient = microsecs / us_PerHour;
    reste = microsecs % us_PerHour;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ":";

    quotient = reste / us_PerMinute;
    reste = reste % us_PerMinute;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ":";

    quotient = reste / us_PerSecond;
    reste = reste % us_PerSecond;
    hmsi += adjustLengthTo2(quotient);
    hmsi += ",";

    quotient = reste / us_PerMillisec;
    hmsi += adjustLengthTo3(quotient);
    return hmsi;
}


/* ********************************************************************************************************** */
/*!
 * \brief   Returns a raw HMSI value ("HHMMSSII").
 *
 * Le premier paramètre \a microsecs est la valeur à convertir en microsecondes. \br
 * Le second paramètre \a framerate est le framerate à utiliser pour le raw hmsi. \br
 * \b Exemple: Transforme 1'234'000'000 en "00203400".
 */
QString Converter::microsecsToRawHMSI(qint64 microsecs, double framerate)
{
    qint64 quotient;
    qint64 reste;
    qint64 conv = us_PerSecond / (qint64)framerate;
    QString hmsi = "";

    if (microsecs == 0) return "00000000";
    if (microsecs < 0) {
        hmsi += "-";
        microsecs = abs(microsecs);
    }
    quotient = microsecs / us_PerHour;
    reste = microsecs % us_PerHour;
    hmsi += adjustLengthTo2(quotient);

    quotient = reste / us_PerMinute;
    reste = reste % us_PerMinute;
    hmsi += adjustLengthTo2(quotient);

    quotient = reste / us_PerSecond;
    reste = reste % us_PerSecond;
    hmsi += adjustLengthTo2(quotient);

    quotient = reste / conv;
    hmsi += adjustLengthTo2(quotient);
    return hmsi;
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Returns a readable HMSI value with days ("N days HH:MM:SS:II").
 *
 * \b Exemple: Transforme 1'234'000'000 en "0 days 00:20:34,000".
 *
 * \a microsecs : microsecs value to convert.
 */
 QString Converter::microsecsToDHMSM(qint64 microsecs)
{
    // si microsecs est inférieur à 24h, alors on retourne "HH:MM:SS,mmm"
    if (microsecs < us_PerDay)
        return microsecsToHMSM(microsecs);
    // Sinon, on retourne "x days" + "HH:MM:SS,mmm"
    else
    {
        qint64 nb_days = microsecs / us_PerDay;
        qint64 day_time =  microsecs % us_PerDay;
        QString day = (nb_days == 1)? " day + " : " days + ";
        return QString::number(nb_days) + day + microsecsToHMSM(day_time);
    }
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Transforme une unité quelconque (string) en microsecondes (numerique).
 *
 * Retourne un nombre de microsecondes. Retourne -1 en cas d'erreur.
 *
 * \a value: un nombre d'unités (string). \br
 * \a conversionFacteur: le facteur de conversion de cette unité. \br
 * \note Hors HMSI.
 */
qint64 Converter::toMicroseconds(QString value, double conversionFacteur)
{
    bool flag;
    // On enlève les espaces qui pouraient faire échouer la conversion.
    // on convertit en double (réel) en raison des secondes.
    double numericValue = value.remove(' ').toDouble(&flag);
    if (flag){
        qint64 microsecValue = floor(numericValue * conversionFacteur);
        return microsecValue;
    }
    else
    {
        qDebug(qPrintable("ERROR: addDigit: converting '" + value + "' to numeric failed !"));
        return -1;
    }
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Change le framerate du NTSC.
 *
 * \a framerate: the new NTSC framerate.
 */
void Converter::setNtscFramePerSec(double framerate)
{
    /*
      * TODO A voir si ca a un sens de faire du NTSC variable ...
        Converter::NtscFramePerSec = framerate;
        Converter::us_PerFrameNTSC = Converter::us_PerSecond / framerate;
    */
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \brief Returns the current NTSC framerate.
 */
 double Converter::getNtscFramePerSec()
{
    return (Converter::NtscFramePerSec);
}



