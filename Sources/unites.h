#ifndef UNITES_H
#define UNITES_H

#include<QMap>

class Unites
{

    public:
        // Liste des énumérés
        enum Units
        {
            HMSI,
            DHMSM,
            SECONDS,
            FRAMES_25,
            FRAMES_50,
            FRAMES_NTSC,
            MILLISECONDS,
            MICROSECONDS
        };

    public:
        Unites();

        static QMap<Units, qint32> usPerUnit;
        static QMap<Units, qint64> maxValue;
        static QMap<Units, double> frameRate;
        static QMap<Units, qint8> nbDecimals;
        static QMap<Units, QString> name;


    /* ****************************************************************
     * Fonction d'initialisation des tables
     * **************************************************************** */
    private :
        void InitMaxValue();
        void InitUsPerUnit();
        void InitframeRate();
        void InitNbDecimals();
        void InitNames();
};

#endif // UNITES_H
