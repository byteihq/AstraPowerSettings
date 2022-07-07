// Copyright 2022 byteihq

#include "Utils.h"
#include <dirent.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>

bool Utils::IsDeviceCharging() {
    bool result = false;
    const std::string powerDirPath("/sys/class/power_supply/");
    DIR *powerDir = opendir(powerDirPath.c_str());
    if (!powerDir) {
        return result;
    }
    dirent *subDir = nullptr;
    while ((subDir = readdir(powerDir)) != nullptr) {
        std::string subDirName(subDir->d_name);
        if (subDirName.find('.') == std::string::npos) {
            std::ifstream charging(powerDirPath + "/" + subDirName + "/status");
            if (!charging.is_open()) {
                continue;
            }
            std::string status;
            std::getline(charging, status);
            std::transform(status.begin(), status.end(), status.begin(), [](char c) { return std::tolower(c); });
            if (status == "charging") {
                result = true;
                break;
            }
        }
    }

    closedir(powerDir);

    return result;
}

int Utils::GetPowerCapacity() {
    int result = -1;
    const std::string powerDirPath("/sys/class/power_supply/");
    DIR *powerDir = opendir(powerDirPath.c_str());
    if (!powerDir) {
        return result;
    }
    dirent *subDir = nullptr;
    while ((subDir = readdir(powerDir)) != nullptr) {
        std::string subDirName(subDir->d_name);
        if (subDirName.find('.') == std::string::npos) {
            std::ifstream capacity(powerDirPath + "/" + subDirName + "/capacity");
            if (!capacity.is_open()) {
                continue;
            }
            std::string tmp;
            std::getline(capacity, tmp);
            try {
                result = std::stoi(tmp);
            } catch (...) {
                continue;
            }
        }
    }

    closedir(powerDir);

    return result;
}

void Utils::Measure(int duration) {
    auto startCapacity = GetPowerCapacity();
    if (startCapacity == -1) {
        std::cout << "Не удалось получить текущий процент заряда. Измерение невозможно";
        return;
    }
    std::cout << "Программа готова к проведению измерений. Нажмите любую клавишу для продолжения" << std::endl;
    std::cin.get();
    auto copyDuration = duration;
    while (copyDuration > 0) {
        std::cout << "Результаты будут готовы через " << copyDuration << " min" << std::endl;
        --copyDuration;
        sleep(60);
    }
    auto endCapacity = GetPowerCapacity();
    if (endCapacity == -1) {
        std::cout << "Не удалось получить текущий процент заряда. Измерение невозможно";
        return;
    }
    if (startCapacity <= endCapacity) {
        std::cout << "Время проведения измерения слишком малое";
        return;
    }
    std::cout << "Начальный заряд: " << startCapacity << "%\n"
              << "Конечный заряд: " << endCapacity << "%\n"
              << "Время измерения: " << duration << " min\n"
              << "Среднее потребление: " << 60./duration * (startCapacity - endCapacity) << "% за 1 час\n"
              << "Полное возможное время работы: " << 100. / (startCapacity - endCapacity) * duration << " min\n"
              << "Оставшееся время работы: "
              << static_cast<float>(endCapacity) / (startCapacity - endCapacity) * duration << " min\n";
}
