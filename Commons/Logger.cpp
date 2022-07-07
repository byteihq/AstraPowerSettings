// Copyright 2022 byteihq

#include "Logger.h"
#include "Presets.h"

#include <iostream>

Logger::Logger() : Out("./log", std::ios::app) {}

void Logger::Log(const std::string &Msg) {
    time_t rawtime = 0;
    tm *timeinfo = nullptr;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buf[BUFSIZ];
    sprintf(buf, "%02d:%02d:%02d: ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//    std::cout << buf << Msg << std::endl;
    Out << buf << Msg << std::endl;
}

void Logger::WriteOutput(const std::string &Path, const std::string &Buffer) {
    std::ofstream out(Path, std::ios::app);
    out << Buffer;
    out.close();
}

Logger::~Logger() {
    Out.close();
}

Logger *Logger::GetInstance() {
    static Logger logger;
    return &logger;
}
