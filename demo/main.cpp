// Copyright 2022 byteihq

#include "Logger.h"
#include "Terminal.h"
#include "Presets.h"
#include "Utils.h"
#include <unistd.h>
#include <stdarg.h>
#include <iostream>
#include <cstring>

static std::string Path = "/home/";

std::string InsertParams(const char *ExecCommand, ...) {
    char res[BUFSIZ];
    std::memset(res, 0, BUFSIZ);
    va_list vaArgList{};
    va_start(vaArgList, ExecCommand);
    vsnprintf(res, BUFSIZ - 1, ExecCommand, vaArgList);
    va_end(vaArgList);
    return res;
}

bool Test(const std::string &TestName, const std::string &ExecCommand, const std::string &FileName = "",
          const std::string &SpecialConditions = "") {
    Logger::GetInstance()->Log(TestName + "_TEST");
    Logger::GetInstance()->Log(TestName + "_COMMAND: " + ExecCommand);
    auto res = Terminal::Exec(ExecCommand);
    if (!res.first) {
        Logger::GetInstance()->Log(TestName + "_TEST Failed");
    }

    if (!FileName.empty()) {
        Logger::GetInstance()->Log(TestName + "_OUTPUT:\n" + res.second);
        Logger::GetInstance()->WriteOutput(Path + "/" + FileName, res.second);
        Logger::GetInstance()->Log(TestName + "_FILE: " + Path + "/" + FileName);
    }

    return res.second.find(SpecialConditions) != std::string::npos;
}

int main(int argc, char *argv[]) {
    if (getuid()) {
        std::cout << "Запустите программу от имени супер пользователя" << std::endl;
        return -1;
    }

    TLPParams tlpParams;
    USERParams userParams;
    TESTSParams testsParams;

    for (size_t i = 0; i < argc; ++i) {
        if (i == 0) {
            continue;
        }
        std::string arg(argv[i]);
        if (!(arg.size() > 2 && arg[0] == '-' && arg[1] == '-')) {
            continue;
        }
        int pos = arg.find('=');
        if (pos == std::string::npos) {
            continue;
        }
        std::string param(arg.begin() + 2, arg.begin() + pos);
        std::string value(arg.begin() + pos + 1, arg.end());
        if (param == "user") {
            userParams.UserName = std::move(value);
        } else if (param == "config_path") {
            tlpParams.Path = std::move(value);
        } else if (param == "tests_enabled") {
            if (value == "true") {
                testsParams.Enabled = true;
            }
        } else if (param == "tests_duration") {
            try {
                testsParams.Duration = std::stoi(value);
                if (testsParams.Duration < 5) {
                    std::cout << "Время измерения может быть недостаточным. Минимальное рекомендуемое время измерения - 5 минут" << std::endl;
                }
            } catch (...) {}
        }
    }

    Path += userParams.UserName;

    Test("TLP_INSTALL", TLP_INSTALL, TLP_INSTALL_OUT);
    Test("TLP_SET_CONFIG", InsertParams(TLP_SET_CONFIG, tlpParams.Path.c_str()));
    if (!testsParams.Enabled) {
        return 0;
    }

    while (Utils::IsDeviceCharging()) {
        std::cout << "Отключить ноутбук от зарядки. Для продолжения нажмите любую клавишу" << std::endl;
        std::cin.get();
    }

    Utils::Measure(testsParams.Duration);

    return 0;
}
