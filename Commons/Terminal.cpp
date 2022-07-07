// Copyright 2022 byteihq

#include "Terminal.h"
#include "Presets.h"

std::pair<bool, std::string> Terminal::Exec(const std::string &cmd) {
    int iErrorLevel = 0;
    char buffer[BUFSIZ];
    std::string result;
    FILE *pipe = popen(std::string(cmd + " 2>&1").c_str(), "r");
    if (!pipe) {
        ++iErrorLevel;
    }
    if (!iErrorLevel) {
        try {
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                result += buffer;
            }
        } catch (...) {
            ++iErrorLevel;
        }
    }
    if (pipe) {
        pclose(pipe);
    }
    if (!result.empty()) {
        result.erase(result.end() - 1);
    }
    return {!iErrorLevel, result};
}
