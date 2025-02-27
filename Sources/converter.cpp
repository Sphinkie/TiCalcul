#include "converter.h"

Converter::Converter()
{
    NtscFramePerSec = 30.0;    // 30 ou 29.97 images par seconde
    us_PerFrameNTSC = us_PerSecond / NtscFramePerSec;

}

    /****************************************************************************
     * Convertit un HMSI (même incomplet) en un nombre de micro-secondes.
     * Ex:  "02:45:00:00" pour 2h45m.
     * @param hmsi_string : hmsi to convert.
     * @param framerate : le framerate utilisé dans le hmsi
     * @return the value converted in microseconds.
     ****************************************************************************/
long Converter::HMSItoMicroseconds(String hmsi_string, double framerate)
    {
        int len = hmsi_string.length();
        long microsecs = 0L;
        if (len > 0)
            microsecs += Character.getNumericValue(hmsi_string.charAt(0)) * 10 * Converter.us_PerHour;  // 10 H
        if (len > 1)
            microsecs += Character.getNumericValue(hmsi_string.charAt(1)) * Converter.us_PerHour;  // 1 H
        if (len > 2)
            microsecs += Character.getNumericValue(hmsi_string.charAt(2)) * 10 * Converter.us_PerMinute;  // 10 min
        if (len > 3)
            microsecs += Character.getNumericValue(hmsi_string.charAt(3)) * Converter.us_PerMinute;  // 10 min
        if (len > 4)
            microsecs += Character.getNumericValue(hmsi_string.charAt(4)) * 10 * Converter.us_PerSecond;  // 10 sec
        if (len > 5)
            microsecs += Character.getNumericValue(hmsi_string.charAt(5)) * Converter.us_PerSecond;  // 1 sec
        if (len > 6)
            microsecs += Character.getNumericValue(hmsi_string.charAt(6)) * 10 * Converter.us_PerSecond/framerate;  // 10 img
        if (len > 7)
            microsecs += Character.getNumericValue(hmsi_string.charAt(7)) * Converter.us_PerSecond/framerate;  // 1 img
        return microsecs;
    }


    /***************************************************************************
     * Convertit un Raw HMSI en un nombre de micro-secondes.
     * Ex:  "0245" pour 2h45m.
     * @param hmsi : raw hmsi to convert.
     * @param framerate : the framerate used for raw hmsi
     * @return the value converted in microseconds.
     ****************************************************************************/
long Converter::convertRawHMSItoMicroseconds(QString hmsi, double framerate)
    {
        long microsecs;
        // String hmsi_num = hmsi.replace('X', '0');
        // On complete hmsi avec des zéros
        QString hmsi_num = QString.format("%1$-8s", hmsi);   // on complete avec des espaces
        hmsi_num = hmsi_num.replace(' ', '0');  // on remplace les espaces par des '0'
        QString digits = hmsi_num.substring(0, 2);                // [0..2[
        microsecs = Integer.parseInt(digits) * us_PerHour;       // hours
        digits = hmsi_num.substring(2, 4);                       // [2..4[
        microsecs += Integer.parseInt(digits) * us_PerMinute;    // minutes
        digits = hmsi_num.substring(4, 6);
        microsecs += Integer.parseInt(digits) * us_PerSecond;    // seconds
        microsecs += Integer.parseInt(hmsi_num.substring(6, 8)) * (us_PerSecond/framerate); // frames
        return microsecs;
    }

    /***************************************************************************
     * Transforme une valeur en une string de 3 chars.
     * Complète avec des zéro, et ne garde que les 3 chiffres les plus significatifs.
     * Exemples:  25 devient "025", 4512 devient "451".
     * @param value : numeric value to complete.
     * @return the value completed with 0s (string size 3 chars).
     ****************************************************************************/
QString Converter::adjustLengthTo3(long value)
    {
        QString str_value = String.valueOf(value);
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
            return str_value.substring(0,3);
        }
    }

    /***************************************************************************
     * Transforme une valeur en une string de 2 chars. Transforme 5 en "05".
     * @param value : numeric value to complete.
     * @return the value completed with 0s (string size 2 chars).
     *************************************************************************** */
QString Converter::adjustLengthTo2(long value) {
        QString str_value = String.valueOf(value);
        if (str_value.length() == 1)
            return "0" + str_value;
        else
            return str_value;
    }

    /***************************************************************************
     * Transforme "123" en "12:3.:..:..".
     * @param raw_hmsi : raw hmsi to convert.
     * @return the hmsi formatted with : and dots.
     ****************************************************************************/
QString Converter::completeRawHMSIWithDots(QString raw_hmsi)
    {
        StringBuilder hmsi = new StringBuilder("..:..:..:..");
        int len = raw_hmsi.length();
        if (len > 0)
            hmsi.setCharAt(0, raw_hmsi.charAt(0));
        if (len > 1)
            hmsi.setCharAt(1, raw_hmsi.charAt(1));
        if (len > 2)
            hmsi.setCharAt(3, raw_hmsi.charAt(2));
        if (len > 3)
            hmsi.setCharAt(4, raw_hmsi.charAt(3));
        if (len > 4)
            hmsi.setCharAt(6, raw_hmsi.charAt(4));
        if (len > 5)
            hmsi.setCharAt(7, raw_hmsi.charAt(5));
        if (len > 6)
            hmsi.setCharAt(9, raw_hmsi.charAt(6));
        if (len > 7)
            hmsi.setCharAt(10, raw_hmsi.charAt(7));
        return hmsi.toString();
    }

    /***************************************************************************
     * On transforme "1234000000" en "1 234".
     * @param microsecs : microsecs value to convert.
     * @return the value converted in seconds.
     ****************************************************************************/
QString Converter::microsecsToSeconds(long microsecs)
    {
        double numericValue = (double) microsecs / us_PerSecond;
        DecimalFormat df = new DecimalFormat("0");
        df.setMaximumFractionDigits(3);
        QString formattedValue = df.format(numericValue);
        formattedValue = formattedValue.replace(',','.');    // replace le , par .
        return addSpaceSeparator(formattedValue);
    }

    /***************************************************************************
     * Convertit un nombre de microsecondes en un nombre de frames (selon un certains framerate)
     * Ex: "1_234_000_000" ms en 25fps donne "30_850" frames.
     * Ex; "1_234_000_000" ms en 50 fps donne "61_700" frames.
     * @param microsecs : microsecs value to convert.
     * @param framerate : framerate to use for conversion (ex: 25.0)
     * @return the value converted in frames.
     ****************************************************************************/
QString Converter::microsecsToFrames(long microsecs, double framerate)
    {
        long numericValue = (long)Math.ceil(microsecs / 1000000.0 * framerate);
        QString stringValue = String.valueOf(numericValue);
        return addSpaceSeparator(stringValue);
    }

    /***************************************************************************
     * On transforme "1_234_000_000" en "1_1234_000".
     * @param microsecs : microsecs value to convert.
     * @return the value converted in milliseconds.
     ****************************************************************************/
QString Converter::microsecsToMillis(long microsecs)
    {
        long numericValue = microsecs / 1_000L;
        QString stringValue = String.valueOf(numericValue);
        return addSpaceSeparator(stringValue);
    }

    /***************************************************************************
     * On transforme une valeur numérique (ex:"1234000000") en un texte avec des espaces
     * (ex: "1 234 000 000").
     * @param microsecs : microsecs value to convert.
     * @return a readable string with space separators.
     ****************************************************************************/
QString Converter::microseconds(long microsecs)
    {
        QString value = String.valueOf(microsecs);
        return addSpaceSeparator(value);
    }

    /***************************************************************************
     * Ajoute des séparateurs de milliers sur la partie entière et la partie décimale.
     * @param value : a numeric value.
     * @return a readable string with space separators.
     ****************************************************************************/
QString Converter::addSpaceSeparator(QString value)
    {
        // 12 345.678 9
        StringBuilder formattedValue = new StringBuilder();
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
            // on ajoute au debut
            formattedValue.insert(0, value.charAt(i));
            if ((lastUnit - i+1) % 3 == 0)
                formattedValue.insert(0, " ");
        }
        // ----------------------------------------------------
        // Cas où il n'y a pas de Partie décimale:
        // ----------------------------------------------------
        if (nombreEntier) return formattedValue.toString();
        // ----------------------------------------------------
        // Cas avec Partie décimale: .678 9
        // ----------------------------------------------------
        formattedValue.append(".");
        // La partie décimale va de pointPos+1 à nbDigits-1
        for (int i = pointPos+1; i <= nbDigits-1; i++)
        {
            // if ((i-pointPos+1) % 3 == 0) formattedValue = formattedValue + " ";
            formattedValue.append(value.charAt(i));
        }
        return formattedValue.toString();
    }

    /***************************************************************************
     * On transforme "1234000000" en "00:20:34:00".
     * @param microsecs : microsecs value to convert.
     * @param framerate : the framerate to use for the 2 last digits.
     * @return a readable HMSI value (HH:MM:SS:II).
     ****************************************************************************/
QString Converter::microsecsToHMSI(long microsecs, double framerate)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == null) return "..:..:..:..";
        if (microsecs == 0) return "00:00:00:00";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = Math.abs(microsecs);
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
        quotient = (long)Math.ceil(reste / 1000000.0 * framerate);
        hmsi += adjustLengthTo2(quotient);
        return hmsi;
    }

    /***************************************************************************
     * On transforme "1234000000" en "00:20:34,000".
     * @param microsecs : microsecs value to convert.
     * @return a readable HMSm value (HH:MM:SS,mmm).
     ****************************************************************************/
QString Converter::microsecsToHMSM(long microsecs)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == null) return "..:..:..,...";
        if (microsecs == 0) return "00:00:00,000";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = Math.abs(microsecs);
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

    /***************************************************************************
     * On transforme 1234000000 en "00203400".
     * @param microsecs : microsecs value to convert.
     * @param framerate : framerate for raw hmsi
     * @return a raw HMSI value ("HHMMSSII").
     ****************************************************************************/
  QString Converter::microsecsToRawHMSI(long microsecs, double framerate)
    {
        long quotient;
        long reste;
        QString hmsi = "";
        if (microsecs == null) return "";
        if (microsecs == 0) return "00000000";
        if (microsecs < 0) {
            hmsi += "-";
            microsecs = Math.abs(microsecs);
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
 QString Converter::microsecsToDHMSM(long microsecs)
    {
        if (microsecs == null) return "";
        // si microsecs est inférieur à 24h, alors on retourne le HMSM
        if (microsecs < us_PerDay)
            return microsecsToHMSM(microsecs);
        // Sinon, on retourne "x days" + "HH:MM:SS,mmm"
        else
        {
            long nb_days = microsecs / us_PerDay;
            long day_time =  microsecs % us_PerDay;
            QString day = (nb_days == 1)? " day + " : " days + ";
            return nb_days + day + microsecsToHMSM(day_time);
        }
    }

    /***************************************************************************
     * Change le framerate du NTSC.
     * @param framerate : the new NTSC framerate.
     ****************************************************************************/
 void Converter::setNtscFramePerSec(double framerate)
    {
        Converter.NtscFramePerSec = framerate;
        Converter.us_PerFrameNTSC = Converter.us_PerSecond / framerate;
    }

    /***************************************************************************
     * Retourne le framerate courant du NTSC.
     * @return the current NTSC framerate.
     ****************************************************************************/
 double Converter::getNtscFramePerSec()
    {
        return (Converter.NtscFramePerSec);
    }



