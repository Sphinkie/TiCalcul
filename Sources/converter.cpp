#include "converter.h"

/*! **************************************************************************
 * \brief Constructeur.
 * ****************************************************************************/
Converter::Converter()
{
/*
 *  * On initialise le NTSC à 30 fps.
    NtscFramePerSec = 30.0;    // 30 ou 29.97 images par seconde
    us_PerFrameNTSC = us_PerSecond / NtscFramePerSec;
*/}

/** **************************************************************************
 * Convertit un HMSI (même incomplet) en un nombre de micro-secondes.
 * Ex:  "02:45:00:00" pour 2h45m.
 * Attention: digitValue() renvoie -1 si ce n'est pas une valeur numérique...
 * @param hmsi_string : hmsi to convert.
 * @param framerate : le framerate utilisé dans le hmsi
 * @return the value converted in microseconds.
 ****************************************************************************/
qint64 Converter::HMSItoMicroseconds(QString hmsi_string, double framerate)
    {
        int len = hmsi_string.length();
        qint64 microsecs = 0L;
        if (len > 0)
            microsecs += hmsi_string.at(0).digitValue() * 10 * Converter::us_PerHour;  // 10 H
        if (len > 1)
            microsecs += hmsi_string.at(1).digitValue() * Converter::us_PerHour;  // 1 H
        if (len > 2)
            microsecs += hmsi_string.at(2).digitValue() * 10 * Converter::us_PerMinute;  // 10 min
        if (len > 3)
            microsecs += hmsi_string.at(3).digitValue() * Converter::us_PerMinute;  // 1 min
        if (len > 4)
            microsecs += hmsi_string.at(4).digitValue() * 10 * Converter::us_PerSecond;  // 10 sec
        if (len > 5)
            microsecs += hmsi_string.at(5).digitValue() * Converter::us_PerSecond;  // 1 sec
        if (len > 6)
            microsecs += hmsi_string.at(6).digitValue() * 10 * Converter::us_PerSecond/framerate;  // 10 img
        if (len > 7)
            microsecs += hmsi_string.at(7).digitValue() * Converter::us_PerSecond/framerate;  // 1 img
        return microsecs;
    }


 /** *************************************************************************
 * Convertit un Raw HMSI en un nombre de micro-secondes.
 * Ex:  "0245" pour 2h45m.
 * @param hmsi : raw hmsi to convert.
 * @param framerate : the framerate used for raw hmsi
 * @return the value converted in microseconds.
 ****************************************************************************/
qint64 Converter::convertRawHMSItoMicroseconds(QString hmsi, double framerate)
    {
        // FIXME : completement no sense
        qint64 microsecs = 0;
        QString hmsi_num = QString::number(microsecs).leftJustified(8,' ');   // on complete avec des espaces
        hmsi_num = hmsi_num.replace(' ', '0');  // on remplace les espaces par des '0'
        microsecs = hmsi_num.left(2).toInt() * us_PerHour;                  // [0..1] hours
        microsecs += hmsi_num.mid(2, 2).toInt() * us_PerMinute;             // [2..3] minutes
        microsecs += hmsi_num.mid(4, 2).toInt() * us_PerSecond;             // [4..5] seconds
        microsecs += hmsi_num.mid(6, 2).toInt() * (us_PerSecond/framerate); // [6..7] frames
        return microsecs;
        // TODO: vérifier que le toInt fonctionne bien s'il y a des espaces
    }

 /** *************************************************************************
 * Transforme une valeur en une string de 3 chars.
 * Complète avec des zéro, et ne garde que les 3 chiffres les plus significatifs.
 * Exemples:  25 devient "025", 4512 devient "451".
 * @param value : numeric value to complete.
 * @return the value completed with 0s (string size 3 chars).
 ****************************************************************************/
QString Converter::adjustLengthTo3(long value)
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

 /** *************************************************************************
 * Transforme une valeur en une string de 2 chars. Transforme 5 en "05".
 * @param value : numeric value to complete.
 * @return the value completed with 0s (string size 2 chars).
 *************************************************************************** */
QString Converter::adjustLengthTo2(long value)
    {
        QString str_value;
        str_value.setNum(value);
        if (str_value.length() == 1)
            return "0" + str_value;
        else
            return str_value;
    }

 /** *************************************************************************
 * Transforme "123" en "12:3.:..:..".
 * @param raw_hmsi : raw hmsi to convert.
 * @return the hmsi formatted with : and dots.
 ****************************************************************************/
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

/*! *************************************************************************
 * On transforme "1234000000" en "1 234".
 * \param microsecs : microsecs value to convert.
 * \return the value converted in seconds.
 * ***************************************************************************/
QString Converter::microsecsToSeconds(qint64 microsecs)
{
    QString formattedValue;
    double numericValue = (double) microsecs / us_PerSecond;
    /*
    DecimalFormat df = new DecimalFormat("0");
    df.setMaximumFractionDigits(3);
    QString formattedValue = df.format(numericValue);
    */
    formattedValue.setNum(numericValue);
    formattedValue = formattedValue.replace(',','.');    // replace le , par .
    return formattedValue;
}

/** *************************************************************************
 * Convertit un nombre de microsecondes en un nombre de frames (selon un certains framerate)
 * Ex: "1_234_000_000" ms en 25fps donne "30_850" frames.
 * Ex; "1_234_000_000" ms en 50 fps donne "61_700" frames.
 * @param microsecs : microsecs value to convert.
 * @param framerate : framerate to use for conversion (ex: 25.0)
 * @return the value converted in frames.
 ****************************************************************************/
QString Converter::microsecsToFrames(qint64 microsecs, double framerate)
    {
    QString stringValue;
        long numericValue = (long)ceil(microsecs / 1000000.0 * framerate);
        stringValue.setNum(numericValue);
        return stringValue;
    }

/*! **************************************************************************
 * On transforme "1_234_000_000" en "1_1234_000".
 * \param microsecs : microsecs value to convert.
 * \return the value converted in milliseconds.
 * ***************************************************************************/
QString Converter::microsecsToMillis(qint64 microsecs)
    {
        QString stringValue;
        stringValue.setNum(microsecs / 1000);
        return stringValue;
    }

/*! *************************************************************************
 * On transforme une valeur numérique (ex: 1234000000) en un texte
 * (ex: "1234000000").
 * \param microsecs : microsecs value to convert.
 * \return a readable string
 * ***************************************************************************/
QString Converter::microseconds(qint64 microsecs)
    {
        return QString::number(microsecs);
    }

/*! **************************************************************************
 * Ajoute des séparateurs de milliers sur la partie entière et la partie décimale.
 * \param value : a numeric value.
 * \return a readable string with space separators.
 * ***************************************************************************/
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

/*! **************************************************************************
 * On transforme "1234000000" en "00:20:34:00".
 * \param microsecs : microsecs value to convert.
 * \param framerate : the framerate to use for the 2 last digits.
 * \return a readable HMSI value (HH:MM:SS:II).
 * ***************************************************************************/
QString Converter::microsecsToHMSI(qint64 microsecs, double framerate)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == -1) return "..:..:..:..";    // TODO : A vérifier
        if (microsecs == 0) return "00:00:00:00";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = abs(microsecs);
        }
        quotient = microsecs / us_PerHour;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ":";
        reste = microsecs % us_PerHour;
        quotient = reste / us_PerMinute;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ":";
        reste = reste % us_PerMinute;
        quotient = reste / us_PerSecond;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ":";
        reste = reste % us_PerSecond;
        // quotient = reste / us_PerFrame;
        quotient = (long)ceil(reste / 1000000.0 * framerate);
        hmsi += adjustLengthTo2(quotient);
        return hmsi;
    }

/*! **************************************************************************
 * On transforme "1234000000" en "00:20:34,000".
 * \param microsecs : microsecs value to convert.
 * \return a readable HMSm value (HH:MM:SS,mmm).
 * ***************************************************************************/
QString Converter::microsecsToHMSM(qint64 microsecs)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == NULL) return "..:..:..,...";   // TODO : A vérifier
        if (microsecs == 0) return "00:00:00,000";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = abs(microsecs);
        }
        quotient = microsecs / us_PerHour;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ":";
        reste = microsecs % us_PerHour;
        quotient = reste / us_PerMinute;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ":";
        reste = reste % us_PerMinute;
        quotient = reste / us_PerSecond;
        hmsi += adjustLengthTo2(quotient);
        hmsi += ",";
        reste = reste % us_PerSecond;
        quotient = reste / us_PerMillisec;
        hmsi += adjustLengthTo3(quotient);
        return hmsi;
    }

/*! **************************************************************************
 * On transforme 1234000000 en "00203400".
 * @param microsecs : microsecs value to convert.
 * @param framerate : framerate for raw hmsi
 * @return a raw HMSI value ("HHMMSSII").
 * ***************************************************************************/
  QString Converter::microsecsToRawHMSI(qint64 microsecs, double framerate)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == NULL) return "";  // TODO : A vérifier
        if (microsecs == 0) return "00000000";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = abs(microsecs);
        }
        quotient = microsecs / us_PerHour;
        hmsi += adjustLengthTo2(quotient);

        reste = microsecs % us_PerHour;
        quotient = reste / us_PerMinute;
        hmsi += adjustLengthTo2(quotient);

        reste = reste % us_PerMinute;
        quotient = reste / us_PerSecond;
        hmsi += adjustLengthTo2(quotient);

        reste = reste % us_PerSecond;
        quotient = reste / (us_PerSecond / (long)framerate);
        hmsi += adjustLengthTo2(quotient);
        return hmsi;
    }

    /***************************************************************************
     * On transforme "1234000000" en "0 days 00:20:34,000".
     * @param microsecs : microsecs value to convert.
     * @return a readable HMSI value with days ("N days HH:MM:SS:II").
     ****************************************************************************/
 QString Converter::microsecsToDHMSM(qint64 microsecs)
    {
        if (microsecs == NULL) return "";    // TODO : A vérifier
        // si microsecs est inférieur à 24h, alors on retourne le HMSM
        if (microsecs < us_PerDay)
            return microsecsToHMSM(microsecs);
        // Sinon, on retourne "x days" + "HH:MM:SS,mmm"
        else
        {
            long nb_days = microsecs / us_PerDay;
            long day_time =  microsecs % us_PerDay;
            QString day = (nb_days == 1)? " day + " : " days + ";
            return QString::number(nb_days) + day + microsecsToHMSM(day_time);
        }
    }

    qint64 Converter::toMicroseconds(QString value, double conversionFacteur)
    {
        bool flag;
        // On enleve les espaces qui font échouer la conversion.
        double numericValue = value.remove(' ').toDouble(&flag);
        if (flag){
            qint64 microsecValue = (qint64)(numericValue * conversionFacteur);
            // TODO voir si on utilise floor() pour être sûr de prendre la valeur entière
            return microsecValue;
        }
        else
        {
            qDebug(qPrintable("ERROR: addDigit: converting '" + value + "' to numeric failed !"));
            return -1;
        }
    }


    /** *************************************************************************
  * Change le framerate du NTSC.
  * @param framerate : the new NTSC framerate.
  ****************************************************************************/
    void Converter::setNtscFramePerSec(double framerate)
    {
    /*
      * TODO A voir si ca a un sens de faire du NTSC variable ...
        Converter::NtscFramePerSec = framerate;
        Converter::us_PerFrameNTSC = Converter::us_PerSecond / framerate;
    */
    }

/** *************************************************************************
 * Retourne le framerate courant du NTSC.
 * @return the current NTSC framerate.
 ****************************************************************************/
 double Converter::getNtscFramePerSec()
    {
        return (Converter::NtscFramePerSec);
    }



