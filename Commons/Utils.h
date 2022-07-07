// Copyright 2022 byteihq

#ifndef ASTRAPOWERSETTINGS_UTILS_H
#define ASTRAPOWERSETTINGS_UTILS_H

#include <string>

class Utils {
private:
    // Возвращает заряд батареи в %
    static int GetPowerCapacity();
public:

    // Возвращает true, если ноутбук на зарядке
    static bool IsDeviceCharging();

    // Проводит измерения энергопотребления
    static void Measure(int duration);
};


#endif //ASTRAPOWERSETTINGS_UTILS_H
