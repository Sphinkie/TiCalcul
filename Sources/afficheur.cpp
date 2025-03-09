#include "afficheur.h"

#include "converter.h"

/*! ***************************************************************
 * \brief Constructeur.
 * \param unit : l'unité correspondante à cet afficheur.
 *****************************************************************/
Afficheur::Afficheur(Unites::Units unit, QObject *parent)
{
    this->mDisplayValue = "UNDEFINED";
    this->mUnit = unit;
    this->mName = Unites::name.value(unit);
    this->mDecimals = Unites::nbDecimals.value(unit);   // nombre de chiffres après la virgule
//    this->mMaxValue = Unites::maxValue.value(unit);     // valeur max : 99 heures.
    this->mFrameRate = Unites::frameRate.value(unit);
    this->mConversionFacteur = Unites::usPerUnit.value(unit);
}

/*! ***************************************************************
 * \brief Permet de changer dynamiquement le framerate des afficheurs HMSI.
 * \note Attention: voir aussi recalculateValeurPivot() de la classe fille.
 * \param framerate: le nouveau framerate pour cet afficheur (ex: 25.0)
 *****************************************************************/
void Afficheur::setFrameRate(double framerate)
{
    this->mFrameRate = framerate;
    this->mConversionFacteur = Converter::us_PerSecond / framerate;
}

/*! ***************************************************************
 * \brief Ajoute un digit à la fin de la chaine de caractères.
 * La nouvelle valeur Pivot, si elle a changé.
 * \param digit: Le caractère digit à ajouter.
 ******************************************************************/
void Afficheur::addDigit(QString digit)
{
    // ------------------------------------------------------------
    // Controles
    // TODO faire le tests sur le Unit
    // ------------------------------------------------------------
    qDebug(qPrintable("addDigit: " + mDisplayValue + " + " + digit));
    // ------------------------------------------------------------
    // Si c'est un un point et qu'il y en a déjà un: on l'ignore
    if ((digit == ".") && mDisplayValue.contains(".")) return;
    // ------------------------------------------------------------
    // Si c'est un point et qu'on est au début: on traite comme "0."
    if ((digit == ".") && mDisplayValue.isEmpty())     digit="0.";
    // ------------------------------------------------------------
    // Si c'est un zéro et qu'on est au début: on l'ignore
    // Sauf pour HMSI et SECONDS qui ont le droit de commencer par un "0"
    if ((this->mName != "HMSI") && (this->mName != "SECONDS"))
        if ((digit == "0") && mDisplayValue.isEmpty()) return;
    // ------------------------------------------------------------
    // Si c'est un 00 et qu'on est au début: on l'ignore (Sauf pour HMSI)
    if ((this->mName != "HMSI") && (digit == "00") && mDisplayValue.isEmpty()) return;
    // ------------------------------------------------------------
    // S'il y a dejà 3 décimales: on n'en ajoute plus
    int len = mDisplayValue.length();
    int pointPos = mDisplayValue.indexOf('.');
    if ((pointPos>-1) && (pointPos < len-3)) return;
    // ------------------------------------------------------------
    // S'il y a déjà 8 chiffres dans le HMSI: on l'ignore
    if ((this->mName == "HMSI") && (len>=8)) return;
    // ------------------------------------------------------------------------
    // On ajoute le digit à stringValue
    // ------------------------------------------------------------------------
    QString newStringValue = mDisplayValue + digit;
    qDebug(qPrintable("candidate: " + newStringValue));

    // ------------------------------------------------------------------------
    // On convertit la StringValue en microsecondes (ValeurPivot)
    // ------------------------------------------------------------------------
    // Cas du HMSI:
    // TODO : cas du D+HMSM
    // ------------------------------------------------------------------------
    if (this->mName == "HMSI")
    {
        emit setValeurPivot(Converter::HMSItoMicroseconds(newStringValue, mFrameRate));
        return;
    }
    // ------------------------------------------------------------------------
    // Autres cas: valeurs numériques
    // ------------------------------------------------------------------------
    else
    {
        bool flag;
        // Valeur MAX non atteinte: on met à jour la valeur pivot.
        // On enleve les espaces qui font échouer la conversion.
        qint64 numericValue = newStringValue.remove(' ').toLongLong(&flag);
        if (flag){
        qint64 microsecValue = numericValue * this->mConversionFacteur;

        qDebug("to send (unit) : %d", numericValue);
        qDebug("to send (us) : %d", numericValue);
        qDebug(qPrintable(newStringValue + " sent!"));

        // TODO voir si on utilise floor() pour être sûr de prendre la valeur entière
        emit setValeurPivot(microsecValue);
        return;
        }
        else
            qDebug(qPrintable("ERROR: addDigit: converting '" + newStringValue + "' to numeric failed !"));
    }
}

/*! ***************************************************************
 * Enlève un digit à la fin de la chaine de caractères.
 * La nouvelle valeur pivot est envoyée à l'opérande (si elle a changé).
 ******************************************************************/
void Afficheur::removeLastDigit()
{
    int len = this->mDisplayValue.length();
    if (len == 0)
    {
        //this->mDisplayValue = "";
        return ;
    }
    else if (len == 1)
    {
        //this->mDisplayValue = "";
        emit setValeurPivot(0);
        return;
    }
    else
    {
        QString newStringValue = this->mDisplayValue.chopped(1);  // Enleve le dernier caractère
        if (this->mUnit == Unites::HMSI)
        {
            // Format HMSI
            emit setValeurPivot(Converter::convertRawHMSItoMicroseconds(newStringValue, this->mFrameRate));
            return;
        }
        else if (this->mUnit == Unites::DHMSM)
        {
            // Format D+HMSm
            // TODO A regrouper avec le précedent
            emit setValeurPivot(Converter::convertRawHMSItoMicroseconds(newStringValue, this->mFrameRate));
            return;
        }
        else
        {
            // Autres formats: on applique simplement le facteur de convertion
            qint64 numericValue = newStringValue.toDouble();
            emit setValeurPivot((qint64)(numericValue * this->mConversionFacteur));
            return;
        }
    }
}

/*! ***************************************************************
 * Vide la chaine à afficher.
 ******************************************************************/
void Afficheur::clearDisplayValue()
{
    setDisplayValue("");
}

/*! ***************************************************************
     * Renvoie le champ textuel en cours de saisie.
     * \returns the currently edited text field.
     ******************************************************************/
QString Afficheur::displayValue() const
{
    QString rawValue = this->mDisplayValue;
    if (this->mDisplayValue == "HMSI")
        // pour le HMSI: on doit compléter avec des .. et des :
        return Converter::completeRawHMSIWithDots(rawValue);
    else
        return Converter::addSpaceSeparator(rawValue);
}

/*! ***************************************************************
 * Retourne le framerate (utile pour les afficheurs HMSI).
 * \returns framerate utilisé pour cet afficheur (ex: 25.0)
 *****************************************************************/
double Afficheur::getFrameRate()
{
    return this->mFrameRate;
}

/*! ***************************************************************
 * Renvoie le nombre de digits déjà présents dans la string.
 * \returns the number of digits in the string.
 ******************************************************************/
int Afficheur::length()
{
    return this->mDisplayValue.length();
}

/*! ***************************************************************
     * Indique si le HMSI a besoin d'être rectifié
     * cad si minutes > 59 ou secondes > 59 ou images > 24.
     * \param rawHmsi : un RAW HMSI du type HHMMSSII
     * \returns true if HMSI needs to be rectified
     ***************************************************************** */
bool Afficheur::isIncorrect(QString rawHmsi)
{
    QString MM = "00";
    QString SS = "00";
    QString II = "00";
    int len = rawHmsi.length();
    // On décortique le rawHMSI en 4 substrings.
    switch (len)
    {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        MM = rawHmsi.mid(2,1);
        break;
    case 4:
        MM = rawHmsi.mid(2,2);
        break;
    case 5:
        MM = rawHmsi.mid(2,2);
        SS = rawHmsi.mid(4,1);
        break;
    case 6:
        MM = rawHmsi.mid(2,2);
        SS = rawHmsi.mid(4,2);
        break;
    case 7:
        MM = rawHmsi.mid(2,2);
        SS = rawHmsi.mid(4,2);
        II = rawHmsi.mid(6,1);
        break;
    case 8:
        MM = rawHmsi.mid(2,2);
        SS = rawHmsi.mid(4,2);
        II = rawHmsi.mid(6,2);
        break;
    default:
        MM = rawHmsi.mid(2,2);
        SS = rawHmsi.mid(4,2);
        II = rawHmsi.mid(6,2);
        break;
    }
    // On vérifie les 4 substring
    if (MM.toInt() > 59) return true;
    if (SS.toInt() > 59) return true;
    if (II.toInt() >= ceil(mFrameRate)) return true;
    return false;
}

/*! ***************************************************************
     * Renvoie le libellé de l'unité correspondant à cet afficheur.
     * \returns the name of the unit
     ******************************************************************/
QString Afficheur::getName()
{
    return mName;
}

/*! ***************************************************************
     * SLOT. Recoit la valeur numérique à afficher.
     * \param microsecs: La valeur pivot en microsecondes.
     ******************************************************************/
void Afficheur::setValue(qint64 microsecs)
{
    QString value = "DEFAULT VALUE";
    switch (mUnit)
    {
    case Unites::HMSI:
        value = Converter::microsecsToHMSI(microsecs, mFrameRate);
        break;
    case Unites::DHMSM:
        value = Converter::microsecsToDHMSM(microsecs);
        break;
    case Unites::FRAMES_25:
        value = Converter::microsecsToFrames(microsecs, 25);
        break;
    case Unites::FRAMES_50:
        value = Converter::microsecsToFrames(microsecs, 50);
        break;
    case Unites::FRAMES_NTSC:
        value = Converter::microsecsToFrames(microsecs, 30);
        break;
    case Unites::SECONDS:
        value = Converter::microsecsToSeconds(microsecs);
        break;
    case Unites::MILLISECONDS:
        value = Converter::microsecsToMillis(microsecs);
        break;
    case Unites::MICROSECONDS:
        value = Converter::microseconds(microsecs);
        break;
    default:
        value="UNKNOWN UNIT";
    }

    setDisplayValue(value);
}

/*!
 * Mémorise et propage la string à afficher vers le QML .
 * \param value: La valeur exprimée dans l'unité de cet afficheur.
 */
void Afficheur::setDisplayValue(QString value)
{
    mDisplayValue = value;
    emit displayValueChanged(value);
}

