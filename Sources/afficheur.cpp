#include "afficheur.h"

/*****************************************************************
 * Ne pas utiliser cette classe, mais des classes filles
 * (ex: AfficheurCalcul) qui contient une valeur pivot commune.
 * Cette classe offre les méthodes pour ajouter les digits un à un.
 ***************************************************************** */

    /*****************************************************************
     * Constructeur
     * @param unit : l'unité correspondante à cet afficheur
     *****************************************************************/
    Afficheur::Afficheur(Unites unit)
        {
            this->mStringValue = "";
            this->mName = unit.name();
            this->mDecimals = unit.nbDecimals();   // nombre de chiffres après la virgule
            this->mMaxValue = unit.maxValue();     // valeur max : 99 heures.
            this->mFrameRate = unit.frameRate();
            this->mConversionFacteur = unit.usPerUnit();
        }

        /*****************************************************************
     * Permet de changer dynamiquement le framerate des afficheurs HMSI.
     * Attention: voir aussi recalculateValeurPivot() de la classe fille.
     * @param framerate : le nouveau framerate pour cet afficheur (ex: 25.0)
     *****************************************************************/
    void Afficheur::setFrameRate(double framerate)
        {
            this->mFrameRate = framerate;
            this->mConversionFacteur = Converter.us_PerSecond / framerate;
        }

        /*****************************************************************
     * Ajoute un digit à la fin de la chaine de caractères
     * @param digit : le caractère digit à ajouter
     * @return Retourne la nouvelle valeur Pivot, ou 'null' si elle ne change pas
     ******************************************************************/
    long Afficheur::_addDigit(QString digit)
        {
            // ------------------------------------------------------------
            // Controles
            // ------------------------------------------------------------
            int len = mStringValue.length();
            // ------------------------------------------------------------
            // Si c'est un un point et qu'il y en a déjà un: on l'ignore
            if ((digit.equals(".")) && mStringValue.contains(".")) return null;
            // ------------------------------------------------------------
            // Si c'est un point et qu'on est au début: on traite comme "0."
            if ((digit.equals(".")) && mStringValue.isEmpty()) this.mStringValue ="0";
            // ------------------------------------------------------------
            // Si c'est un zéro et qu'on est au début: on l'ignore
            // Sauf pour HMSI et SECONDS qui ont le droit de commencer par un "0"
            if ((!this->name().equals("HMSI")) && (!this.name().equals("SECONDS")))
                if ((digit.equals("0")) && mStringValue.isEmpty()) return null;
            // ------------------------------------------------------------
            // Si c'est un 00 et qu'on est au début: on l'ignore (Sauf pour HMSI)
            if ((!thisqname().equals("HMSI")) && (digit.equals("00")) && mStringValue.isEmpty()) return null;
            // ------------------------------------------------------------
            // S'il y a dejà 3 décimales: on n'en ajoute plus
            int pointPos = mStringValue.indexOf('.');
            if ((pointPos>-1) && (pointPos < len-3)) return null;
            // ------------------------------------------------------------
            // S'il y a déjà 8 chiffres dans le HMSI: on l'ignore
            if ((this->name().equals("HMSI")) && (len>=8)) return null;
            // ------------------------------------------------------------
            // s'il y a deja un trailing zero, on enleve le zéro (sauf si digit="." et sauf pour HMSI)
            if ((mStringValue.equals("0")) && (!digit.equals(".")) && (!this.name().equals("HMSI")))
            {
                mStringValue = "";
                len = 0;
            }
            // ------------------------------------------------------------------------
            // On ajoute le digit à stringValue
            // ------------------------------------------------------------------------
            QString newStringValue = mStringValue + digit;
            double numericValue = Double.parseDouble(newStringValue);
            // On vérifie qu'on ne dépasse pas la valeur max autorisée
            if (numericValue > mMaxValue)
            {
                // Si dépassement: Alarme et on ne touche pas aux valeurs
                // Si le toast est deja affiché, on ne le ré-affiche pas.
                if (!PopupMessage.isShown())
                {
                    //PopupMessage.showToast(R.string.msg_max_reached, true);
                    PopupMessage.showSnack(R.string.msg_max_reached, true);
                }
                return null;
            }
            // ------------------------------------------------------------------------
            // On convertit la StringValue en microsecondes (ValeurPivot)
            // ------------------------------------------------------------------------
            // Cas du HMSI:
            // ------------------------------------------------------------------------
            else if (this->name().equals("HMSI"))
            {
                // Valeur MAX non atteinte: on met à jour la valeur pivot.
                this.mStringValue = newStringValue;
                return Converter.HMSItoMicroseconds(newStringValue, mFrameRate);
            }
            // ------------------------------------------------------------------------
            // Autres cas: valeurs numériques
            // ------------------------------------------------------------------------
            else
            {
                // Valeur MAX non atteinte: on met à jour la valeur pivot.
                this.mStringValue = newStringValue;
                // voir si on utilise floor() pour être sûr de prendre la valeur entière
                return (long)(numericValue * this->mConversionFacteur);
            }
        }

        /*****************************************************************
     * Enlève un digit à la fin de la chaine de caractères.
     * @return : la nouvelle valeur pivot
     ******************************************************************/
    long Afficheur::_removeLastDigit()
        {
            int len = this->mStringValue.length();
            if (len == 0)
            {
                this->mStringValue = "";
                return null;
            }
            else if (len == 1)
            {
                this->mStringValue = "";
                return 0L;
            }
            else
            {
                this->mStringValue = this.mStringValue.substring(0,len-1);
                if (this.name().equals("HMSI"))
                {
                    // Format HMSI
                    return Converter.convertRawHMSItoMicroseconds(this.mStringValue, this.mFrameRate);
                }
                else
                {
                    // Autres formats: on applique simplement le facteur de convertion
                    double numericValue = Double.parseDouble(this.mStringValue);
                    return (long)(numericValue * this.mConversionFacteur);
                }
            }
        }

        /*****************************************************************
     * Vide la valeur.
     ******************************************************************/
    void Afficheur::clear()
        {
            this->mStringValue ="";
        }

        /*****************************************************************
     * Renvoie le champ textuel en cours de saisie.
     * @return the currently edited text field.
     ******************************************************************/
    QString Afficheur::getStringValue()
        {
            QString rawValue = this.mStringValue;
            if (this->name().equals("HMSI"))
                // pour le HMSI: on doit compléter avec des .. et des :
                return Converter.completeRawHMSIWithDots(rawValue);
            else
                return Converter.addSpaceSeparator(rawValue);
        }

        /*****************************************************************
     * Retourne le framerate (utile pour les afficheurs HMSI).
     * @return framerate utilisé pour cet afficheur (ex: 25.0)
     *****************************************************************/
    double Afficheur::getFrameRate()
        {
            return this->mFrameRate;
        }

        /*****************************************************************
     * Renvoie le nombre de digits déjà présents dans la string.
     * @return the number of digits in the string.
     ******************************************************************/
    int Afficheur::length()
        {
            return this->mStringValue.length();
        }

        /*****************************************************************
     * Indique si le HMSI a besoin d'etre rectifié
     * cad si minutes > 59, ou secondes > 59 ou images > 24.
     * @param rawHmsi : un RAW HMSI du type HHMMSSII
     * @return true if HMSI needs to be rectified
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
            case 4:
                MM = rawHmsi.substring(2,len);
                break;
            case 5:
            case 6:
                MM = rawHmsi.substring(2,4);
                SS = rawHmsi.substring(4,len);
                break;
            case 7:
            case 8:
                MM = rawHmsi.substring(2,4);
                SS = rawHmsi.substring(4,6);
                II = rawHmsi.substring(6,len);
                break;
            default:
                MM = rawHmsi.substring(2,4);
                SS = rawHmsi.substring(4,6);
                II = rawHmsi.substring(6,8);
                break;
            }
            // On vérifie les 4 substring
            if (Integer.parseInt(MM) > 59) return true;
            if (Integer.parseInt(SS) > 59) return true;
            if (Integer.parseInt(II) >= Math.ceil(mFrameRate)) return true;
            return false;
        }

        /*****************************************************************
     * Renvoie le nom de l'instance, qui indique l'unité correspondante.
     * @return the name of the instance
     ******************************************************************/
    QString Afficheur::name()
        {
            return mName;
        }

    }




