#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
public:
    Settings();
    int SAFEGAP;
    int SPEEDLIMIT;
    double ACC;
    int FPS;
    void updateSettings(int safeGap, int speedLimit, double acc, int fps);
};

#endif // SETTINGS_H
