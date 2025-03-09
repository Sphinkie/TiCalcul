#ifndef UNITES_H
#define UNITES_H

#include<QMap>
#include "converter.h"

class Unites
{

    public:
        // Liste des énumérés
        enum Units
        {
            HMSI,
            DHMSM,
            FRAMES_25,
            FRAMES_50,
            FRAMES_NTSC,
            SECONDS,
            MILLISECONDS,
            MICROSECONDS
        };

    public:
        Unites();

        static const inline QMap<Units, qint32> usPerUnit ={
            {HMSI, Converter::us_PerFrame25}, {DHMSM, Converter::us_PerFrame25},
            {FRAMES_25, Converter::us_PerFrame25} , {FRAMES_50,Converter::us_PerFrame50}, {FRAMES_NTSC, Converter::us_PerFrameNTSC},
            {SECONDS, Converter::us_PerSecond}, {MILLISECONDS,1000}, {MICROSECONDS,1}
        };
        /*
        //! TODO Ne sert plus à rien
        static const inline QMap<Units, qint64> maxValue = {
            {HMSI,99999999}, {DHMSM,99999999},
            {FRAMES_25, 99 * 60 * 60 * 25} , {FRAMES_50, 99 * 60 * 60 * 50}, {FRAMES_NTSC, 99 * 60 * 60 * 30},
            {SECONDS, 99 * 60 * 60}, {MILLISECONDS, 99 * 60 * 60 * 1000}, {MICROSECONDS, 99 * 60 * 60 * (qint64)(1000000)}
        };
        */
        static const inline QMap<Units, double> frameRate = {
            {HMSI,25.0}, {DHMSM,25.0},
            {FRAMES_25, 25.0} , {FRAMES_50, 50.0}, {FRAMES_NTSC, 30.0},
            {SECONDS,1.0}, {MILLISECONDS, 1000.0}, {MICROSECONDS, 1000000.0}
        };
        static const inline QMap<Units, qint8> nbDecimals = {
            {HMSI, 0}, {DHMSM, 0},
            {FRAMES_25, 0} , {FRAMES_50, 0}, {FRAMES_NTSC, 0},
            {SECONDS, 3}, {MILLISECONDS, 0}, {MICROSECONDS, 0}
        };
        static const inline QMap<Units, QString> name = {
            {HMSI,"HMSI"}, {DHMSM,"DHMSM"},
            {FRAMES_25, "FRAMES_25"} , {FRAMES_50, "FRAMES_50"}, {FRAMES_NTSC, "FRAMES_NTSC"},
            {SECONDS, "SECONDS"}, {MILLISECONDS, "MILLISECONDS"}, {MICROSECONDS, "MICROSECONDS"}
        };


    /* ****************************************************************
     * Fonction d'initialisation des tables
     * NOTE : A supprimer
     * **************************************************************** */
    private :
        static void InitMaxValue();
        static void InitUsPerUnit();
        static void InitframeRate();
        static void InitNbDecimals();
        static void InitNames();
};

#endif // UNITES_H
