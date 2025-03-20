#include <QRegularExpression>
#include "afficheur.h"
#include "converter.h"

/*! **********************************************************************************************************
 * \brief Constructeur.
 * \param unit : l'unité correspondante à cet afficheur.
 * ***********************************************************************************************************/
Afficheur::Afficheur(Unites::Units unit, QString parentName, QObject *parent)
{
    this->mDisplayValue = "";
    this->mUnit = unit;
    this->mHint = Unites::hint.value(unit);
    this->mUnitName = Unites::name.value(unit);
    this->mFramerate = Unites::frameRate.value(unit);
    this->mConversionFacteur = Unites::usPerUnit.value(unit);
    setObjectName(parentName + '_' + mUnitName);
}

/*! **********************************************************************************************************
 * \brief Permet de changer dynamiquement le framerate des afficheurs HMSI.
 * \note C'est toujours l'afficheur HMSI qui reçoit ce signal
 * \param framerate: le nouveau framerate pour cet afficheur (ex: 25.0)
 * ***********************************************************************************************************/
void Afficheur::setFramerate(double framerate)
{
    qint64 microsecValue;
    qDebug() << this->objectName() << "setFramerate" << framerate;
    // On lit l'ancienne valeur
    microsecValue = Converter::HMSItoMicroseconds(mDisplayValue, mFramerate);

    // On prend en compte le nouveau framerate
    this->mFramerate = framerate;
    this->mConversionFacteur = Converter::us_PerSecond / framerate;
    // On signale le changement de framerate au QML
    emit framerateChanged();

    // On met à jour l'affichage du HMSI
    if (mUnit == Unites::HMSI)
    {
        if (this->mIsActive)
        {
            // On actualise la valeur pivot,
            microsecValue = Converter::rawHMSItoMicroseconds(mRawHMSI, mFramerate);
            // On demande le raffraichissement de tous les afficheurs
            emit setValeurPivot(microsecValue);
        }
        else
        {
            // la valeur pivot n'a pas besoin d'être modifiée (on reprend l'ancienne valeur),
            // mais le HMSI doit être recalculé et re-affiché (juste sur cet afficheur).
            this->setValue(microsecValue);
        }
    }
    else
    {
        qDebug() << "Warning: setFramerate received by non HMSI display" << this->objectName();
    }
}

/*! **********************************************************************************************************
 * \brief Ajoute un digit à la fin de la chaine de caractères.
 * \note  Met à jour la nouvelle valeur Pivot, si elle a changé.
 * \param digit: Le caractère digit à ajouter.
 * ***********************************************************************************************************/
void Afficheur::addDigit(QString digit)
{
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
        qint64 numericvalue = Converter::rawHMSItoMicroseconds(mRawHMSI, mFramerate);
        emit setValeurPivot(numericvalue);
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

/*! **********************************************************************************************************
 * Enlève un digit à la fin de la chaine de caractères.
 * La nouvelle valeur pivot est envoyée à l'opérande.
 * ***********************************************************************************************************/
void Afficheur::removeLastDigit()
{
    // si la chaine est dejà vide , on sort.
    if ( this->mDisplayValue.length() == 0)  return;
    // Sinon, on efface le dernier caractère.
    switch (mUnit)
    {
    case Unites::HMSI:
        // Format HMSI
        this->mRawHMSI.chop(1);  // Enleve le dernier caractère
        emit setValeurPivot(Converter::rawHMSItoMicroseconds(mRawHMSI, this->mFramerate));
        break;
    case Unites::DHMSM:
        // TODO : Format D+HMSmm  (si nécéssaire - en V2)
        this->mRawHMSI.chop(1);  // Enleve le dernier caractère
        emit setValeurPivot(Converter::rawHMSItoMicroseconds(mRawHMSI, this->mFramerate));
        break;
    default:
    {
        // Autres units: on applique simplement le facteur de convertion
        this->mRawNUM.chop(1);  // Enleve le dernier caractère
        qDebug(qPrintable("candidate: " + mRawNUM));
        bool ok;
        // normalement, il n'y a pas d'espaces dans le RawNUM, mais par securité, on les enlève.
        double numericValue = this->mRawNUM.remove(' ').toDouble(&ok);
        if (ok){
            qint64 microsecValue = (qint64)(numericValue * this->mConversionFacteur);
            emit setValeurPivot(microsecValue);
        }
        else {
            qDebug(qPrintable("ERROR: removeLastDigit: converting '" + mRawNUM + "' to numeric failed. Replace with 0"));
            emit setValeurPivot(0);
        }
        break;
    }
    }
}


/*! **********************************************************************************************************
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
    if (II.toInt() >= ceil(mFramerate)) return true;
    return false;
}

/*! **********************************************************************************************************
 * \brief SLOT: Actualise la variable mIsActive en cas de changement
 * \param afficheur: Le nom (objectName) de l'afficheur sélectionné dans le QML.
 * ***********************************************************************************************************/
void Afficheur::activeDisplay(QString afficheur)
{
    // qDebug() << "activeDisplay = " << afficheur;
    mIsActive = (afficheur == this->objectName());
    // Quand l'afficheur passe actif, on recharge les valeurs éditables avec les valeurs en cours.
    if (mIsActive)
    {
        mRawHMSI = Converter::HMSItoRawHMSI(mDisplayValue);
        // on enlève les 0 et les espaces du début
        static QRegularExpression regex = QRegularExpression("^[0\\s]*");
        mRawNUM  = mDisplayValue.remove(regex);
        qDebug() << "mRawNUM" << mRawNUM;
    }
}


/*! **********************************************************************************************************
 * \brief SLOT: Efface la valeur de l'afficheur, et ses variables privées.
 * ***********************************************************************************************************/
void Afficheur::clearValue()
{
    qDebug() << objectName() << "::clearValue()";
    mRawHMSI.clear();
    mRawNUM.clear();
    mDisplayValue.clear();
    emit displayValueChanged();
}


/*! **********************************************************************************************************
 * \brief SLOT. Recoit la nouvelle valeur pivot de l'opérande, pour la convertir et l'envoyer à l'affichage.
 * \param microsecs: La valeur pivot en microsecondes.
 * \param force: true pour forcer l'affichage de la valeur du paramètre microsecs
 * \see signal Operande::valeurPivotChanged()
 * *********************************************************************************************************** */
void Afficheur::setValue(const qint64 microsecs, const bool force)
{
    qDebug() << this->objectName() << "::setValue()" << microsecs;
    QString value = "";
    switch (mUnit)
    {
    case Unites::HMSI:
        value = Converter::microsecsToRawHMSI(microsecs, mFramerate);
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
    // On mémorise et on envoie à l'affichage QML.
    this->setDisplayValue(value, force);
}


/*! **********************************************************************************************************
 * \brief Mémorise et propage la string à afficher vers le QML.
 * \note On distingue le cas où la cellule est active (cad en cours d'édition), ou pas.
 *       Si la cellule est active, on ignore la valeur reçue et on continue d'afficher la
 *       valeur brute qui est en cours d'édition.
 * \param value: La valeur brute exprimée dans l'unité de cet afficheur (rawHMSI ou rawNUM).
 * \param force: si true, on prend en compter la valeur, meme si l'afficheur est actif.
 * ***********************************************************************************************************/
void Afficheur::setDisplayValue(const QString value, const bool force)
{
    qDebug() << this->objectName() << "::setDisplayValue" << value << (mIsActive? "active": "passive");

    // Si le champ est en cours d'édition, et que l'on ne force pas l'affichage de la nouvelle valeur:
    if (mIsActive && !force)
    {
        switch (mUnit)
        {
            case Unites::HMSI:
                // On affiche la valeur en cours d'édition (mRawHMSi)
                mDisplayValue = Converter::completeRawHMSIWithDots(mRawHMSI);
                break;
            default:
                // Pour les autres unités, on affichera la valeur en cours d'édition, avec des séparateurs
                mDisplayValue = Converter::addSpaceSeparator(mRawNUM);
                break;
        }
    }
    // Sinon: la cellule est en affichage uniquement
    else
    {
        switch (mUnit)
        {
            case Unites::HMSI:
                // on affiche la valeur recue (complète)
                mDisplayValue = Converter::completeRawHMSIWithDots(value);
                break;
            case Unites::DHMSM:
                // Pour le D+HMSm, on affichera telle quelle la valeur reçue (qui est complète)
                mDisplayValue = value;
                break;
            default:
                // Pour les autres unités, on affichera la valeur reçue, avec des séparateurs
                mDisplayValue = Converter::addSpaceSeparator(value);
                break;
        }
    }
    emit displayValueChanged();
}

/*! **********************************************************************************************************
 * \brief Cette fonction remet le HMSI de façon correcte.
 ************************************************************************************************************* */
void Afficheur::rectifyHMSI()
{
    qint64 microsecValue;
    qDebug() << this->objectName() << "rectifyHMSI";

    // On met à jour l'affichage du HMSI
    if (mUnit == Unites::HMSI)
    {
        if (this->mIsActive)
        {
            // En édition: on recalcule le HMSI à partir du RawHMSI
            microsecValue = Converter::rawHMSItoMicroseconds(mRawHMSI, mFramerate);
            mRawHMSI = Converter::microsecsToRawHMSI(microsecValue, mFramerate);
            this->setDisplayValue(mRawHMSI);   // si active, il va prendre le mRawHMSI
        }
        else
        {
            // Hors édition: on recalcule le HMSI à partir du HMSI affiché
            microsecValue = Converter::HMSItoMicroseconds(mDisplayValue, mFramerate);
            // mais le HMSI doit être recalculé et re-affiché (juste sur cet afficheur).
            this->setValue(microsecValue);
        }
    }
    else
    {
        qDebug() << "Warning: rectifyHMSI received by non HMSI display" << this->objectName();
    }
}

