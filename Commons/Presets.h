// Copyright 2022 byteihq

#ifndef ASTRATESTING_PRESETS_H
#define ASTRATESTING_PRESETS_H

#ifdef BUFSIZ
#undef BUFSIZ
#endif
#define BUFSIZ 1024

#include <string>

struct TLPParams {
    std::string Path = "./Misc/tlp";
};

struct USERParams {
    std::string UserName = "u";
};

struct TESTSParams {
    bool Enabled = false;
    int Duration = 5; // 5 min
};

#define TLP_INSTALL "sudo apt install tlp -y"
#define TLP_INSTALL_OUT "tlp_install_info.txt"
#define TLP_SET_CONFIG "sudo cp -rfv %s /etc/default/tlp"

#endif //ASTRATESTING_PRESETS_H
