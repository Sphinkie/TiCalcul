#include "unites.h"


/***************************************************************************
 * Enumérés des différentes unités gérées par l'application.
 * Pour chacune des unités, on a quelques infos utiles, telles que
 * la valeur max affichable dans l'appli, le nombre de décimales à afficher, etc.
 ****************************************************************************/

/*****************************************************************
 * Constructeur. On fixe la valeur max à 99 heures.
 * @param us_per_unit : nombre de microseconds par unité.
 * @param framerate : nombre d'unités par seconde. Doit être cohérent avec us_per_unit.
 * @param decimals : nombre de chiffres après la virgule.
 ******************************************************************/
Unites::Unites(double us_per_unit, double framerate, int decimals)
{
    this->mUsPerUnit = us_per_unit;
    this->mFrameRate = framerate;
    this->mNbDecimals = decimals;
    this->mMaxValue = (long)(99 *60 * 60 * (1000000L / us_per_unit)); // 99 heures
    if (this->name().equals("HMSI"))
        this->mMaxValue =99999999L;
}


/*****************************************************************
* Accesseurs
******************************************************************/
int Unites::nbDecimals()
{
    return mNbDecimals;
}
double Unites::usPerUnit()
{
    return mUsPerUnit;
}
long Unites::maxValue()
{
    return mMaxValue;
}
double Unites::frameRate()
{
    return mFrameRate;
}

