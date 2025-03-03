#include "unites.h"


/***************************************************************************
 * Enumérés des différentes unités gérées par l'application.
 * Pour chacune des unités, on a quelques infos utiles, telles que
 * la valeur max affichable dans l'appli, le nombre de décimales à afficher, etc.
 ****************************************************************************/

/** ***************************************************************
 * Constructeur. On remplit les maps.
 ******************************************************************/
Unites::Unites()
{/*
    InitUsPerUnit();
    InitframeRate();
    InitframeRate();
    InitMaxValue();
    InitNames();
*/
}


/** *****************************************************************
 * @brief Unites::InitUsPerUnit
 * initialise la map usPerUnit qui fournit le nombre de microseconds par unité.
 ******************************************************************/
void Unites::InitUsPerUnit()
{/*
    usPerUnit[HMSI]=Converter::us_PerFrame25;
    usPerUnit[DHMSM]=Converter::us_PerFrame25;
    usPerUnit[SECONDS]=Converter::us_PerSecond;
    usPerUnit[FRAMES_25]=Converter::us_PerFrame25;
    usPerUnit[FRAMES_50]=Converter::us_PerFrame50;
    usPerUnit[FRAMES_NTSC]=Converter::us_PerFrameNTSC;
    usPerUnit[MILLISECONDS]=1000;
    usPerUnit[MICROSECONDS]=1;
*/}

/** *****************************************************************
 * @brief Unites::InitMaxValue
 * initialise la map maxValue qui fournit la valeur max autorisée pour l'unité.
 * (99 heures)
 ********************************************************************/
void Unites::InitMaxValue()
{/*
    maxValue[HMSI] = 99999999;                                      //      99 999 999
    maxValue[DHMSM] = 99999999;                                     //      99 999 999
    maxValue[SECONDS] = 99 * 60 * 60;                               //         356 400
    maxValue[FRAMES_25] = 99 * 60 * 60 * 25;                        //       8 910 000
    maxValue[FRAMES_50] = 99 * 60 * 60 * 50;                        //      17 820 000
    maxValue[FRAMES_NTSC] = 99 * 60 * 60 * 30;
    maxValue[MILLISECONDS] = 99 * 60 * 60 * 1000;                   //     356 400 000
    maxValue[MICROSECONDS] = 99 * 60 * 60 * (qint64)(1000000);      // 356 400 000 000
*/
}

/** *****************************************************************
 * @brief Unites::InitframeRate
 * initialise la map frameRate qui fournit le nombre d'unités par seconde. Doit être cohérent avec us_per_unit..
 */
void Unites::InitframeRate()
{/*
    frameRate[HMSI] = 25.0;
    frameRate[DHMSM] = 25.0;
    frameRate[SECONDS] = 1.0;
    frameRate[FRAMES_25] = 25.0;
    frameRate[FRAMES_50] = 50.0;
    frameRate[FRAMES_NTSC] = 30.0;
    frameRate[MILLISECONDS] = 1000.0;
    frameRate[MICROSECONDS] = 1000000.0;
*/}

/** *****************************************************************
 * @brief Unites::InitNbDecimals
 * initialise la map nbDecimals qui fournit le nombre de chiffres après la virgule.
 */
void Unites::InitNbDecimals()
{/*
    nbDecimals[HMSI] =0 ;
    nbDecimals[DHMSM] = 0;
    nbDecimals[SECONDS] = 3;
    nbDecimals[FRAMES_25] = 0;
    nbDecimals[FRAMES_50] = 0;
    nbDecimals[FRAMES_NTSC] = 0;
    nbDecimals[MILLISECONDS] = 0;
    nbDecimals[MICROSECONDS] = 0;
*/}

/** *****************************************************************
 * @brief Unites::InitNames
 * initialise la map name qui fournit le nom de l'unité sous forme de string.
 */
void Unites::InitNames()
{/*
    name[HMSI]="HMSI";
    name[DHMSM]="DHMSM";
    name[SECONDS]="SECONDS";
    name[FRAMES_25]="FRAMES_25";
    name[FRAMES_50]="FRAMES_50";
    name[FRAMES_NTSC]="FRAMES_NTSC";
    name[MILLISECONDS]="MILLISECONDS";
    name[MICROSECONDS]="MICROSECONDS";
*/
}
