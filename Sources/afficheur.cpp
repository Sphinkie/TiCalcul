#include <QRegularExpression>
#include "afficheur.h"
#include "converter.h"


/* ********************************************************************************************************** */
/*!
 * \class Afficheur
 * \inmodule TiCalcul
 * \title Afficheur avec une unité donnée
 * \brief La classe Afficheur gère un champ numérique de l'IHM QML.
 *
 * Elle est associée à un objet QML FieldInput et lui envoie les valeurs à afficher.
 * Il y a un Afficheur pour chaque unité: Secondes, Millisecondes, HMSI, etc. \br
 * Tous les afficheurs sont liés à un \l Operande. \br
 * Chaque Afficheur exprime cet \l Operande dans une des \l Unites définie lors de sa construction.
 */


/* ********************************************************************************************************** */
/*!
 * \brief Constructeur: On initialise toutes les property de cet afficheur.
 *
 * \a unit : L'unité correspondante à cet afficheur. \br
 * \a parent : QObject parent: un \l Operande. Son nom va servir.
 */
Afficheur::Afficheur(Unites::Units unit, QObject* parent): QObject(parent)
{
    this->mDisplayValue = "";
    this->mUnit = unit;
    this->mHint = Unites::hint.value(unit);
    this->mUnitName = Unites::name.value(unit);
    this->mFramerate = Unites::frameRate.value(unit);
    this->mConversionFacteur = Unites::usPerUnit.value(unit);
    this->mMaxValue = Unites::max.value(unit);
    this->mPartner = this;
    this->mCorrect = true;
    setObjectName(parent->objectName() + '_' + mUnitName);
}


/*************************************************************************************************************/
/*!
 * \brief La fonction findPartner trouve et mémorise l'afficheur partenaire, c'est-à-dire l'afficheur
 * équivalent de l'autre opérande, dont le nom est transmis dans le paramètre \a partnername.
 */
void Afficheur::findPartner(QString partnername)
{

    QString partner = partnername + "_" + mUnitName;
    QObject* root = this->parent()->parent();
    mPartner = root->findChild<Afficheur*>(partner);
    emit partnerChanged();
}


/*************************************************************************************************************/
/*!
 * \brief Afficheur::setNavigation mémorise les Afficheurs qui entourent l'afficheur courant.
 *
 * Les paramètres \a N, \a S, \a E et \a W sont les Afficheurs situés respectivement au Nord, Sud, Est, Ouest.
 */
void Afficheur::setNavigation(Afficheur *N, Afficheur *S, Afficheur *E, Afficheur *W)
{
    // Navigration
    this->mUp = N;
    this->mDown = S;
    this->mRight = E;
    this->mLeft = W;
}


/* ********************************************************************************************************** */
/*!
 * \brief Ce SLOT permet de changer dynamiquement le frameRate des afficheurs HMSI.
 *
 * Note: C'est toujours l'afficheur HMSI qui reçoit ce signal. \br
 * \a new_framerate: le nouveau framerate pour cet afficheur (ex: 25.0).
 */
void Afficheur::setFramerate(double new_framerate)
{
    qint64 microsecValue;
    qDebug() << this->objectName() << "setFramerate" << new_framerate;
    // On lit l'ancienne valeur
    microsecValue = Converter::HMSItoMicroseconds(mDisplayValue, mFramerate);

    // On prend en compte le nouveau framerate
    this->mFramerate = new_framerate;
    this->mConversionFacteur = Converter::us_PerSecond / new_framerate;
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
        qWarning() << "Warning: setFramerate received by non HMSI display" << this->objectName();
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief Ajoute un digit à la fin de la chaine de caractères.
 *
 * Met à jour la nouvelle valeur Pivot, si elle a changé.
 * La nouvelle valeur pivot est envoyée à l'opérande, par le signal setValeurPivot(). \br
 * \a digit: Le caractère digit à ajouter.
 */
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
        if ((digit == ".") && mRawNUM.isEmpty())  mRawNUM="0";
        // ------------------------------------------------------------
        // Si c'est un point, on n'a pas encore de chiffre derrière, on l'affiche aussitot.
        // et on ne modifie pas la valeur pivot.
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
        // Controle de dépassement
        // ------------------------------------------------------------------------
        qDebug(qPrintable("candidate check: " + mRawNUM+digit));
        if ((mRawNUM+digit).remove(' ').toLongLong() > mMaxValue) return;
        qDebug(qPrintable("passed"));
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
        // Controle de dépassement
        // ------------------------------------------------------------------------
        if ((mRawNUM+digit).remove(' ').toLongLong() > mMaxValue) return;
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


/* ********************************************************************************************************** */
/*!
 * \brief Enlève un digit à la fin de la chaine de caractères.
 *
 * La nouvelle valeur pivot est envoyée à l'opérande, par le signal setValeurPivot().
 */
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
            qWarning(qPrintable("ERROR: removeLastDigit: converting '" + mRawNUM + "' to numeric failed. Replace with 0"));
            emit setValeurPivot(0);
        }
        break;
    }
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief Indique si le HMSI a besoin d'être rectifié.
 *
 * Si minutes>59 ou secondes>59 ou images>24, alors le \a raw_hmsi (de type HHMMSSII) a besoin d'être rectifié,
 * et la fonction retourne \c True. \br
 * Gère le cas > 99h.
 */
bool Afficheur::isCorrect(const QString raw_hmsi)
{
    QString MM = "00";
    QString SS = "00";
    QString II = "00";
    int len = raw_hmsi.length();
    // On décortique le rawHMSI en 3 substrings.
    switch (len)
    {
    case 0:
    case 1:  // H
    case 2:  // HH
        break;
    case 3:  // HHM
        MM = raw_hmsi.last(1);
        break;
    case 4:  // HHMM
        MM = raw_hmsi.last(2);
        break;
    case 5:  // HHMMS
        MM = raw_hmsi.mid(2,2);
        SS = raw_hmsi.last(1);
        break;
    case 6:  // HHMMSS
        MM = raw_hmsi.mid(2,2);
        SS = raw_hmsi.last(2);
        break;
    case 7:  // HHMMSSI
        MM = raw_hmsi.mid(2,2);
        SS = raw_hmsi.mid(4,2);
        II = raw_hmsi.last(1);
        break;
    case 8:  // HHMMSSII
        MM = raw_hmsi.mid(2,2);
        SS = raw_hmsi.mid(4,2);
        II = raw_hmsi.last(2);
        break;
    default:  // HH..HHMMSSII  (>99h)
        MM = raw_hmsi.mid(len-6,2);
        SS = raw_hmsi.mid(len-4,2);
        II = raw_hmsi.last(2);
        break;
    }
    // On vérifie les 3 substring
    if (MM.toInt() > 59) return false;
    if (SS.toInt() > 59) return false;
    if (II.toInt() >= ceil(mFramerate)) return false;
    return true;
}


/* ********************************************************************************************************** */
/*!
 * \brief SLOT: Actualise la variable mIsActive en cas de changement de l'afficheur sélectionné dans le QML.
 *
 * Le nom \a afficheur est l'objectName du nouvel Afficheur actif.
 * Voir aussi le signal QML activeDisplay() de l'afficheurActif.
 **/
void Afficheur::activeDisplay(QString afficheur)
{
    qDebug() << this->objectName() << "::activeDisplay <- " << afficheur;
    mIsActive = (afficheur == this->objectName());
    // Quand l'afficheur passe actif, on recharge les valeurs éditables avec les valeurs en cours.
    if (mIsActive)
    {
        mRawHMSI = Converter::HMSItoRawHMSI(mDisplayValue);
        // on enlève les 0 du début et tous les espaces
        static QRegularExpression regex = QRegularExpression("^[0]*|[\\s]*");
        mRawNUM  = mDisplayValue.remove(regex);
        qDebug() << "mRawNUM" << mRawNUM;
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief Le \b slot clearValue() reçoit le signal Operande::valeurPivotCleared() et efface la valeur de
 *        l'afficheur, ainsi que ses variables privées.
 **/
void Afficheur::clearValue()
{
    qDebug() << this->objectName() << "::clearValue()";
    mRawHMSI.clear();
    mRawNUM.clear();
    mDisplayValue.clear();
    mCorrect = true;
    emit displayValueChanged();
    emit correctChanged();
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
/*!
 * \fn void Afficheur::setValue(const qint64 microsecs, const bool force=false)
 * \brief Ce \b slot recoit la nouvelle valeur pivot de l'opérande, pour la convertir et l'envoyer à l'affichage.
 *
 * La fonction setValue() reçoit \a microsecs , la nouvelle valeur pivot, en microsecondes.
 * Elle la convertit dans l'unité de l' \l Afficheur et l'envoie au QMl pour être affichée.
 * Le paramètre \a force précise s'il faut prendre en compte la valeur reçue même si le champ est en cours d'édition.
 * Voir le signal Operande::valeurPivotChanged()
 **/
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


/* ********************************************************************************************************** */
/*!
 * \brief Mémorise et propage la string à afficher vers le QML.
 * \note On distingue le cas où la cellule est active (cad en cours d'édition), ou pas.
 *       Si la cellule est active, on ignore la valeur reçue et on continue d'afficher la
 *       valeur brute qui est en cours d'édition.
 * \a value: La valeur brute exprimée dans l'unité de cet afficheur (rawHMSI ou rawNUM).
 * \a force: si true, on prend en compte la valeur, meme si l'afficheur est actif.
 **/
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
                mCorrect = isCorrect(mRawHMSI);
                emit correctChanged();
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
                mCorrect = isCorrect(value);
                emit correctChanged();
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


/* ********************************************************************************************************** */
/*!
 * \brief La fonction rectifyHMSI() remet le HMSI de façon correcte.
 **/
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
            mCorrect = true;
            emit correctChanged();
        }
    }
    else
    {
        qWarning() << "Warning: rectifyHMSI received by non HMSI display" << this->objectName();
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief La fonction Afficheur::copy() renvoie la valeur brute de l'afficheur, pour être utilisée dans le presse-papier
 *        de Windows, lors d'un copier/coller.
 */
QString Afficheur::copy()
{
    if (mUnit == Unites::HMSI)
    {
        // on retourne le RAW_HMSI propre
        return Converter::rawHMSItoHMSI(mRawHMSI);
    }
    else
    {
        return mRawNUM;
    }
}


/* ********************************************************************************************************** */
/*!
 * \brief La fonction \l paste() rentre la valeur \a value reçue, venant du presse-papier
 *        de Windows, lors d'un copier/coller, dans l'afficheur.
 *
 * Si la valeur est trop grande (99H pour les HMSI) on ignore le paste.
 */
void Afficheur::paste(QString value)
{
    static QRegularExpression anyNondigit = QRegularExpression("\\D");
    static QRegularExpression anyNonDigitPointComma = QRegularExpression("[^\\d\\.,]");

    if (mUnit == Unites::HMSI)
    {
        // On enleve les caractères parasites
        QString filtered = value.remove(anyNondigit);
        // Controle de dépassement: 8 DIGITS MAX
        if (filtered.size() > 8) return;
        // Si OK, on convertit la string en microsecondes
        mRawHMSI = filtered;
        qint64 microsecValue = Converter::rawHMSItoMicroseconds(mRawHMSI, mFramerate);
        // On diffuse la nouvelle ValeurPivot
        emit setValeurPivot(microsecValue);
    }
    else if (mUnit == Unites::SECONDS)
    {
        // on enleve les caractères parasites
        QString filtered = value.remove(anyNonDigitPointComma);
        // On accepte les virgules mais on les remplace par un point
        filtered.replace(',','.');
        // On ne garde que le premier point
        while (filtered.count('.') > 1)
            {
                int n = filtered.indexOf('.');
                filtered.removeAt(n);
            }
        // Controle de dépassement
        if (filtered.toLongLong() > mMaxValue) return;
        // Si OK, on convertit la string en microsecondes
        mRawNUM = filtered;
        qint64 microsecValue = Converter::toMicroseconds(mRawNUM, mConversionFacteur);
        // On diffuse la nouvelle ValeurPivot
        emit setValeurPivot(microsecValue);
    }
    else
    {
        // on enleve les caractères parasites
        QString filtered = value.remove(anyNondigit);
        // Controle de dépassement
        if (filtered.toLongLong() > mMaxValue) return;
        // Si OK, on convertit la string en microsecondes
        mRawNUM = filtered;
        // On convertit la string en microsecondes
        qint64 microsecValue = Converter::toMicroseconds(mRawNUM, mConversionFacteur);
        // On diffuse la nouvelle ValeurPivot
        emit setValeurPivot(microsecValue);
    }
}



/*!
    \property Afficheur::displayValue
    \brief La valeur à afficher dans la GUI.
*/

/*!
    \property Afficheur::framerate
    \brief Le framerate de cet afficheur (pour les HMSI)
*/

/*!
    \property Afficheur::unit
    \brief Le nom de l'unité utilisée par cet afficheur
*/

/*!
    \property Afficheur::hint
    \brief Le texte à afficher si mDisplayValue est vide.
*/

/*!
    \property Afficheur::correct
    \brief Indique que l'afficheur (HMSI) est devenu incorrect (ou correct).
*/

/*!
    \property Afficheur::partner
    \brief L'afficheur équivalent de l'autre opérande..
*/

/*!
    \property Afficheur::up
    \brief Afficheur Nord situé au dessus.
*/

/*!
    \property Afficheur::down
    \brief Afficheur Sud situé au dessous.
*/

/*!
    \property Afficheur::right
    \brief Afficheur Est situé à droite.
*/

/*!
    \property Afficheur::left
    \brief Afficheur West situé à Gauche.
*/
