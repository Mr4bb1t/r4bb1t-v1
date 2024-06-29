#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <Arduino.h>

class BatteryMonitor {
public:
    BatteryMonitor(int pin);
    void begin();
    float getBatteryVoltage();
    int getBatteryPercentage();

private:
    int _pin;
    float readVoltage();
};

#endif // BATTERYMONITOR_H