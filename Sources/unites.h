#ifndef UNITES_H
#define UNITES_H

class Unites
{
public:
    Unites(double us_per_unit, double framerate, int decimals);
    double usPerUnit();
    double frameRate();
    long maxValue();
    int nbDecimals();


    /* ****************************************************************
     * Variables privées de chaque énuméré
     * **************************************************************** */
private :
    double mUsPerUnit;
    double mFrameRate;
    long mMaxValue;
    int mNbDecimals;


    enum Units()
    {
        // Liste des énumérés
            HMSI(Converter.us_PerFrame25,25.0,0),
            DHMSM(Converter.us_PerFrame25,25.0,0),
            SECONDS(Converter.us_PerSecond,1.0, 3),
            FRAMES_25(Converter.us_PerFrame25,25.0, 0),
            FRAMES_50(Converter.us_PerFrame50,50.0, 0),
            FRAMES_NTSC(Converter.us_PerFrameNTSC,30.0, 0),
            MILLISECONDS(1_000,1000.0, 0),
            MICROSECONDS(1,1000000.0, 0);
    }


};

#endif // UNITES_H
