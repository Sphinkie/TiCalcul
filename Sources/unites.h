#ifndef UNITES_H
#define UNITES_H

#include<QMap>
#include "converter.h"


/*! **************************************************************************
 * \class Unites
 * \brief Enumérés des différentes unités gérées par l'application.
 *        Pour chacune des unités, on a quelques infos utiles, telles que
 *        la valeur max affichable dans l'appli, le ratio de conversion, etc.
 *****************************************************************************/
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
            {HMSI, Converter::us_PerFrame25},
            {DHMSM, Converter::us_PerFrame25},
            {FRAMES_25, Converter::us_PerFrame25},
            {FRAMES_50,Converter::us_PerFrame50},
            {FRAMES_NTSC, Converter::us_PerFrameNTSC},
            {SECONDS, Converter::us_PerSecond},
            {MILLISECONDS,Converter::us_PerMillisec},
            {MICROSECONDS,1}
        };

        static const inline QMap<Units, double> frameRate = {
            {HMSI,25.0},
            {DHMSM,25.0},
            {FRAMES_25, 25.0},
            {FRAMES_50, 50.0},
            {FRAMES_NTSC, 30.0},
            {SECONDS,1.0},
            {MILLISECONDS, 1000.0},
            {MICROSECONDS, 1000000.0}
        };

        static const inline QMap<Units, QString> name = {
            {HMSI,"HMSI"},
            {DHMSM,"DHMSM"},
            {FRAMES_25, "FRAMES_25"},
            {FRAMES_50, "FRAMES_50"},
            {FRAMES_NTSC, "FRAMES_NTSC"},
            {SECONDS, "SECONDS"},
            {MILLISECONDS, "MILLISECONDS"},
            {MICROSECONDS, "MICROSECONDS"}
        };

        static const inline QMap<Units, QString> hint = {
            {HMSI,"HH:MM:SS:FF"},
            {DHMSM,"HH:MM:SS,mmm"},
            {FRAMES_25, "FRAMES"},
            {FRAMES_50, "FRAMES"},
            {FRAMES_NTSC, "FRAMES"},
            {SECONDS, "SECONDS"},
            {MILLISECONDS, "MILLISECONDS"},
            {MICROSECONDS, "MICROSECONDS"}
        };

        static const inline QMap<Units, qint64> max = {
            {HMSI,0},
            {DHMSM,0},
            {FRAMES_25,    2499999999},
            {FRAMES_50,    4999999999},
            {FRAMES_NTSC,  3999999999},  // TBC
            {SECONDS,      99999999},
            {MILLISECONDS, 99999999999},
            {MICROSECONDS, 99999999999999}
        };
};

#endif // UNITES_H
