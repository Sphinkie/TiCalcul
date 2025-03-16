#ifndef CONVERTER_H
#define CONVERTER_H
#include <QObject>


/*! *******************************************************************************
 * \class Classe statique contenant des fonctions de conversion de timecodes.
 ********************************************************************************** */
class Converter
{
    /***************************************************************************
     * On définit quelques constantes.
     ****************************************************************************/
    public:
        static const qint64 us_PerHour = 3600000000;
        static const qint64 us_PerDay = us_PerHour * 24;
        static const qint64 us_PerMinute = 60000000;
        static const qint64 us_PerSecond =  1000000;
        static const qint64 us_PerMillisec =   1000;
        static const qint64 us_PerFrame25 = us_PerSecond / 25;
        static const qint64 us_PerFrame50 = us_PerSecond / 50;

        static const inline double NtscFramePerSec = 29.97;
        static const inline double us_PerFrameNTSC = us_PerSecond / NtscFramePerSec;


    /***************************************************************************
     * Les méthodes de conversion.
     ****************************************************************************/
    public:
        Converter();

        static QString addSpaceSeparator(QString value);
        static qint64 HMSItoMicroseconds(QString hmsi_string, double framerate);
        static QString HMSItoRawHMSI(const QString hmsi);
        static qint64 convertRawHMSItoMicroseconds(QString hmsi, double framerate);
        static QString completeRawHMSIWithDots(QString raw_hmsi);
        static QString microsecsToSeconds(qint64 microsecs);
        static QString microsecsToFrames(qint64 microsecs, double framerate);
        static QString microsecsToMillis(qint64 microsecs);
        static QString microseconds(qint64 microsecs);
        static QString microsecsToHMSI(qint64 microsecs, double framerate);
        static QString microsecsToHMSM(qint64 microsecs);
        static QString microsecsToRawHMSI(qint64 microsecs, double framerate);
        static QString microsecsToDHMSM(qint64 microsecs);
        static qint64 toMicroseconds(QString value, double conversionFacteur);

        static void setNtscFramePerSec(double framerate);
        static double getNtscFramePerSec();

    private:
        static QString adjustLengthTo3(qint64 value);
        static QString adjustLengthTo2(qint64 value);

};

#endif // CONVERTER_H
