#include "settings.h"

Settings::Settings()
{

}

void Settings::updateSettings(int safeGap, int speedLimit, double acc, int fps)
{
    this->SAFEGAP = safeGap;
    this->SPEEDLIMIT = speedLimit;
    this->ACC = acc;
    this->FPS = fps;
}
