// Copyright 2022 byteihq

#ifndef ASTRATESTING_LOGGER_H
#define ASTRATESTING_LOGGER_H

#include <string>
#include <fstream>

class Logger {
private:
    std::ofstream Out;

    Logger();
public:
    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    static Logger *GetInstance();

    void Log(const std::string& Msg);

    void WriteOutput(const std::string& Path, const std::string& Buffer);

    ~Logger();
};


#endif //ASTRATESTING_LOGGER_H
