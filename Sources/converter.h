#ifndef CONVERTER_H
#define CONVERTER_H
#include <QObject>


/********************************************************************************
 * Classe statique contenant des fonctions de conversion de timecodes
 * Il s'agit de HMSI bruts (de la forme HHHMMSSII)
 ********************************************************************************/
class Converter
{
    /***************************************************************************
     * On définit quelques constantes.
     ****************************************************************************/
    public:
        static const long us_PerDay = 24 * 3_600_000_000L;
        static const long us_PerHour = 3_600_000_000L;
        static const long us_PerMinute = 60_000_000L;
        static const long us_PerSecond = 1_000_000L;
        static const long us_PerMillisec = 1_000L;
        static const long us_PerFrame25 = us_PerSecond / 25;
        static const long us_PerFrame50 = us_PerSecond / 50;
        // Cas du NTSC (ce n'est pas forcemement une constante)
        static double NtscFramePerSec;    // 30 ou 29.97 images par seconde
        static double us_PerFrameNTSC;

    public:
        Converter();

        static long HMSItoMicroseconds(QString hmsi_string, double framerate);
        static long convertRawHMSItoMicroseconds(QString hmsi, double framerate);
        static QString completeRawHMSIWithDots(QString raw_hmsi);
        static QString microsecsToSeconds(long microsecs);
        static QString microsecsToFrames(long microsecs, double framerate);
        static QString microsecsToMillis(long microsecs);
        static QString microseconds(long microsecs),
        static QString addSpaceSeparator(QString value);
        static QString microsecsToHMSI(long microsecs, double framerate);
        static QString microsecsToHMSM(long microsecs);
        static QString microsecsToRawHMSI(long microsecs, double framerate);
        static QString microsecsToDHMSM(long microsecs);
        static void setNtscFramePerSec(double framerate);
        static double getNtscFramePerSec();

    private:
        static QString adjustLengthTo3(long value);
        static QString adjustLengthTo2(long value);

};

#endif // CONVERTER_H
