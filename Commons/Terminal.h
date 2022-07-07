#ifndef ASTRATESTING_TERMINAL_H
#define ASTRATESTING_TERMINAL_H

#include <string>

class Terminal {
public:

    static std::pair<bool, std::string> Exec(const std::string &cmd);
};


#endif //ASTRATESTING_TERMINAL_H
