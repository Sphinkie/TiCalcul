#include "afficheur.h"

#include "converter.h"

    /*! ***************************************************************
     * Constructeur
     * \param unit : l'unité correspondante à cet afficheur
     *****************************************************************/
    Afficheur::Afficheur(Unites::Units unit, QObject *parent)
        {
            this->mDisplayValue = "UNDEFINED";
            this->mUnit = unit;
            this->mName = Unites::name.value(unit);
            this->mDecimals = Unites::nbDecimals.value(unit);   // nombre de chiffres après la virgule
            this->mMaxValue = Unites::maxValue.value(unit);     // valeur max : 99 heures.
            this->mFrameRate = Unites::frameRate.value(unit);
            this->mConversionFacteur = Unites::usPerUnit.value(unit);
        }

    /*!
     * Permet de changer dynamiquement le framerate des afficheurs HMSI.
     * Attention: voir aussi recalculateValeurPivot() de la classe fille.
     * \param framerate: le nouveau framerate pour cet afficheur (ex: 25.0)
     *****************************************************************/
    void Afficheur::setFrameRate(double framerate)
        {
            this->mFrameRate = framerate;
            this->mConversionFacteur = Converter::us_PerSecond / framerate;
        }

    /*!
     * Ajoute un digit à la fin de la chaine de caractères
     * \param digit: le caractère digit à ajouter
     * \returns Retourne la nouvelle valeur Pivot, ou 'null' si elle ne change pas
     ******************************************************************/
    qint32 Afficheur::_addDigit(QString digit)
        {
            // ------------------------------------------------------------
            // Controles
            // ------------------------------------------------------------
            int len = mDisplayValue.length();
            // ------------------------------------------------------------
            // Si c'est un un point et qu'il y en a déjà un: on l'ignore
            if ((digit == ".") && mDisplayValue.contains(".")) return NULL;
            // ------------------------------------------------------------
            // Si c'est un point et qu'on est au début: on traite comme "0."
            if ((digit == ".") && mDisplayValue.isEmpty()) this->mDisplayValue ="0";
            // ------------------------------------------------------------
            // Si c'est un zéro et qu'on est au début: on l'ignore
            // Sauf pour HMSI et SECONDS qui ont le droit de commencer par un "0"
            if ((this->mName != "HMSI") && (this->mName != "SECONDS"))
                if ((digit == "0") && mDisplayValue.isEmpty()) return NULL;
            // ------------------------------------------------------------
            // Si c'est un 00 et qu'on est au début: on l'ignore (Sauf pour HMSI)
            if ((this->mName != "HMSI") && (digit == "00") && mDisplayValue.isEmpty()) return NULL;
            // ------------------------------------------------------------
            // S'il y a dejà 3 décimales: on n'en ajoute plus
            int pointPos = mDisplayValue.indexOf('.');
            if ((pointPos>-1) && (pointPos < len-3)) return NULL;
            // ------------------------------------------------------------
            // S'il y a déjà 8 chiffres dans le HMSI: on l'ignore
            if ((this->mName == "HMSI") && (len>=8)) return NULL;
            // ------------------------------------------------------------
            // s'il y a deja un trailing zero, on enleve le zéro (sauf si digit="." et sauf pour HMSI)
            if ((mDisplayValue == "0") && (digit != ".") && (this->mName != "HMSI"))
            {
                mDisplayValue = "";
                len = 0;
            }
            // ------------------------------------------------------------------------
            // On ajoute le digit à stringValue
            // ------------------------------------------------------------------------
            QString newStringValue = mDisplayValue + digit;
            qint32 numericValue = newStringValue.toULong();
            // On vérifie qu'on ne dépasse pas la valeur max autorisée
            if (numericValue > mMaxValue)
            {
                // TODO Afficher une erreur "msg_max_reached"
                // console.warning ("msg_max_reached")
                /*
                // Si dépassement: Alarme et on ne touche pas aux valeurs
                // Si le toast est deja affiché, on ne le ré-affiche pas.
                if (!PopupMessage.isShown())
                {
                    //PopupMessage.showToast(R.string.msg_max_reached, true);
                    PopupMessage.showSnack(R.string.msg_max_reached, true);
                }
*/
                return NULL;
            }
            // ------------------------------------------------------------------------
            // On convertit la StringValue en microsecondes (ValeurPivot)
            // ------------------------------------------------------------------------
            // Cas du HMSI:
            // ------------------------------------------------------------------------
            else if (this->mName == "HMSI")
            {
                // Valeur MAX non atteinte: on met à jour la valeur pivot.
                this->mDisplayValue = newStringValue;
                return Converter::HMSItoMicroseconds(newStringValue, mFrameRate);
            }
            // ------------------------------------------------------------------------
            // Autres cas: valeurs numériques
            // ------------------------------------------------------------------------
            else
            {
                // Valeur MAX non atteinte: on met à jour la valeur pivot.
                this->mDisplayValue = newStringValue;
                // voir si on utilise floor() pour être sûr de prendre la valeur entière
                return (long)(numericValue * this->mConversionFacteur);
            }
        }

    /*! ***************************************************************
     * Enlève un digit à la fin de la chaine de caractères.
     * \returns la nouvelle valeur pivot
     ******************************************************************/
    qint32 Afficheur::_removeLastDigit()
        {
            int len = this->mDisplayValue.length();
            if (len == 0)
            {
                this->mDisplayValue = "";
                return NULL;
            }
            else if (len == 1)
            {
                this->mDisplayValue = "";
                return 0L;
            }
            else
            {
                this->mDisplayValue.chop(1);  // Enleve le dernier caractère
                if (this->mName == "HMSI")
                {
                    // Format HMSI
                    return Converter::convertRawHMSItoMicroseconds(this->mDisplayValue, this->mFrameRate);
                }
                else
                {
                    // Autres formats: on applique simplement le facteur de convertion
                    double numericValue = this->mDisplayValue.toDouble();
                    return (long)(numericValue * this->mConversionFacteur);
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
                    value.setNum(microsecs);
                    break;
                default:
                    value="UNKNOWN UNIT";
            }

            setDisplayValue(value);
        }

        /*!
         * Mémorise et propage la string à afficher.
         * \param value: La valeur exprimée dans l'unité de cet afficheur.
         */
        void Afficheur::setDisplayValue(QString value)
        {
            mDisplayValue = value;
            emit displayValueChanged(value);
        }

