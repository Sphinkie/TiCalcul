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
    this->mUnitName = Unites::name.value(unit);
    this->mDecimals = Unites::nbDecimals.value(unit);   // TODO: nombre de chiffres après la virgule
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
 * \note  Met à jour la nouvelle valeur Pivot, si elle a changé.
 * \param digit: Le caractère digit à ajouter.
 ******************************************************************/
void Afficheur::addDigit(QString digit)
{
    // FIXME: on ne peut pas ajouter un (ou plusieurs) 0 après le point.
    switch (mUnit)
    {
    case Unites::HMSI:
    {
        qDebug(qPrintable("addDigit: " + mRawHMSI + " + " + digit));
        // ------------------------------------------------------------------------
        // S'il y a déjà 8 chiffres dans le HMSI: on n'en ajoute plus
        // ------------------------------------------------------------------------
        if (mRawHMSI.length() >= 8) return;
        // ------------------------------------------------------------------------
        // On ajoute le digit à la string
        // ------------------------------------------------------------------------
        mRawHMSI.append(digit);
        qDebug(qPrintable("Raw HMSI candidate: " + mRawHMSI));
        // ------------------------------------------------------------------------
        // On convertit la string en microsecondes (ValeurPivot)
        // ------------------------------------------------------------------------
        emit setValeurPivot(Converter::convertRawHMSItoMicroseconds(mRawHMSI, mFrameRate));
        break;
    }
    case Unites::SECONDS:
    {
        qDebug(qPrintable("addDigit: " + mRawNUM + " + " + digit));
        // ------------------------------------------------------------------------
        // Si c'est un 00 et qu'on est au début: on l'ignore (Sauf pour HMSI)
        // ------------------------------------------------------------------------
        if ((digit == "00") && mRawNUM.isEmpty()) return;
        // ------------------------------------------------------------
        // Si c'est un point et qu'il y en a déjà un: on l'ignore
        // ------------------------------------------------------------
        if ((digit == ".") && mRawNUM.contains("."))  return;
        // ------------------------------------------------------------
        // Si c'est un point et qu'on est au début: on traite comme "0."
        // ------------------------------------------------------------
        if ((digit == ".") && mRawNUM.isEmpty())      digit="0";
        // ------------------------------------------------------------
        // Si c'est un point, on n'a pas encore de chiffre derrière, on l'affiche aussitot.
        // et on ne modifiepas la valeur pivot.
        // ------------------------------------------------------------
        if (digit == ".")
        {
            mDisplayValue.append('.');
            mRawNUM.append('.');
            this->setDisplayValue(mRawNUM);
            return;
        }
        // ------------------------------------------------------------------------
        // S'il y a dejà 3 décimales: on n'en ajoute plus
        // ------------------------------------------------------------------------
        int pointPos = mRawNUM.indexOf('.');
        if ((pointPos > -1) && (pointPos < mRawNUM.length()-3)) return;
        // ------------------------------------------------------------------------
        // On ajoute le digit à la string
        // ------------------------------------------------------------------------
        // newStringValue = mRawNUM + digit;
        mRawNUM.append(digit);
        qDebug(qPrintable("candidate: " + mRawNUM));
        // ------------------------------------------------------------------------
        // On convertit la string en microsecondes (ValeurPivot)
        // ------------------------------------------------------------------------
        qint64 microsecValue = Converter::toMicroseconds(mRawNUM, mConversionFacteur);
        emit setValeurPivot(microsecValue);
        break;
    }
    default:
        qDebug(qPrintable("addDigit: " + mRawNUM + " + " + digit));
        // ------------------------------------------------------------------------
        // Si c'est un zéro et qu'on est au début: on l'ignore
        // Sauf pour HMSI et SECONDS qui ont le droit de commencer par un "0"
        // ------------------------------------------------------------------------
        if ((digit == "0") && mRawNUM.isEmpty())  return;
        // ------------------------------------------------------------
        // Si c'est un 00 et qu'on est au début: on l'ignore (Sauf pour HMSI)
        // ------------------------------------------------------------------------
        if ((digit == "00") && mRawNUM.isEmpty()) return;
        // ------------------------------------------------------------------------
        // On ajoute le digit à la string
        // ------------------------------------------------------------------------
        mRawNUM.append(digit);
        qDebug(qPrintable("candidate: " + mRawNUM));
        // ------------------------------------------------------------------------
        // On convertit la string en microsecondes (ValeurPivot)
        // ------------------------------------------------------------------------
        qint64 microsecValue = Converter::toMicroseconds(mRawNUM, mConversionFacteur);
        emit setValeurPivot(microsecValue);
        break;
    }
}

/*! ***************************************************************
 * Enlève un digit à la fin de la chaine de caractères.
 * La nouvelle valeur pivot est envoyée à l'opérande (si elle a changé).
 ******************************************************************/
void Afficheur::removeLastDigit()
{
    int len = this->mDisplayValue.length();
    if (len == 0)     return ;
    if (len == 1)
    {
        // TODO : emit (clearValeurPivot),
        emit setValeurPivot(0);
        return;
    }
    // TODO : si on efface la première décimale, il faut laisser le point
    QString newStringValue;
    switch (mUnit)
    {
    case Unites::HMSI:
    {
        // Format HMSI
        newStringValue = this->mRawHMSI.chopped(1);  // Enleve le dernier caractère
        emit setValeurPivot(Converter::convertRawHMSItoMicroseconds(newStringValue, this->mFrameRate));
        break;
    }
    case Unites::DHMSM:
    {
        // TODO : Format D+HMSm  (si nécéssaire - V2)
        newStringValue = this->mRawHMSI.chopped(1);  // Enleve le dernier caractère
        emit setValeurPivot(Converter::convertRawHMSItoMicroseconds(newStringValue, this->mFrameRate));
        break;
    }
    default:
    {
        // Autres units: on applique simplement le facteur de convertion
        newStringValue = this->mRawNUM.chopped(1);  // Enleve le dernier caractère
        qDebug(qPrintable("candidate: " + newStringValue));
        bool flag;
        // normalement, il n'y a pas d'espaces dans le RawNUM, mais par securité, on les enlève.
        double numericValue = newStringValue.remove(' ').toDouble(&flag);
        if (flag){
            qint64 microsecValue = (qint64)(numericValue * this->mConversionFacteur);
            emit setValeurPivot(microsecValue);
            return;
        }
        else
            qDebug(qPrintable("ERROR: removeLastDigit: converting '" + newStringValue + "' to numeric failed !"));
        break;
    }
    }
}

/*! ***************************************************************
 * Vide la chaine à afficher.
 ******************************************************************/
void Afficheur::clearDisplayValue()
{
    this->setDisplayValue("");
    mRawHMSI.clear();
    mRawNUM.clear();
}

/*! ***************************************************************
 * Renvoie le champ textuel en cours de saisie.
 * \returns the currently edited text field.
 ******************************************************************/
QString Afficheur::displayValue() const
{/*
    QString rawValue = this->mDisplayValue;
    if (this->mUnit == Unites::HMSI)
        // pour le HMSI: on doit compléter avec des .. et des :
        return Converter::completeRawHMSIWithDots(rawValue);
    else
        return Converter::addSpaceSeparator(rawValue);
*/
    return "";
}

/*! ***************************************************************
 * Retourne le framerate (utile pour les afficheurs HMSI).
 * \returns framerate utilisé pour cet afficheur (ex: 25.0)
 *****************************************************************/
double Afficheur::getFrameRate() const
{
    return this->mFrameRate;
}

/*! ***************************************************************
 * Renvoie le nombre de digits déjà présents dans la string.
 * \returns the number of digits in the string.
 ******************************************************************/
int Afficheur::length() const
{
    return this->mDisplayValue.length();
}

/*! ***************************************************************
 * Indique si le HMSI a besoin d'être rectifié
 * cad si minutes > 59 ou secondes > 59 ou images > 24.
 * \param rawHmsi : un RAW HMSI du type HHMMSSII
 * \returns true if HMSI needs to be rectified
 ***************************************************************** */
bool Afficheur::isIncorrect(const QString rawHmsi)
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
 * Renvoie le libellé de l'unité correspondant à cet afficheur. NOT USED
 * \returns the name of the unit
 ******************************************************************/
QString Afficheur::getUnit() const
{
    return mUnitName;
}

/*! ***************************************************************
 * SLOT. Recoit la nouvelle valeur pivot de l'opérande, pour la connvertir
 * et l'envoyer à l'affichage.
 * \param microsecs: La valeur pivot en microsecondes.
 ******************************************************************/
void Afficheur::setValue(const qint64 microsecs)
{
    QString value = "DEFAULT VALUE";
    switch (mUnit)
    {
    case Unites::HMSI:
        value = Converter::microsecsToRawHMSI(microsecs, mFrameRate);
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
    this->setDisplayValue(value);
}

/*!
 * \brief SLOT: Afficheur::clearValue
 */
void Afficheur::clearValue()
{
    qDebug("clearValue received from Operande");
    mRawHMSI.clear();
    mRawNUM.clear();
    mDisplayValue.clear();
    emit displayValueChanged();
}

/*! ***************************************************************
 * Mémorise et propage la string à afficher vers le QML .
 * \param value: La valeur exprimée dans l'unité de cet afficheur.
 ******************************************************************/
void Afficheur::setDisplayValue(const QString value)
{
    if (mUnit == Unites::HMSI)
        mDisplayValue = Converter::completeRawHMSIWithDots(value);
    else
        mDisplayValue = Converter::addSpaceSeparator(value);
    emit displayValueChanged();
}

