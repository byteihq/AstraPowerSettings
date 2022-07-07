#! /bin/bash

sudo apt install g++ -y

g++ -I./Commons/ ./Commons/Logger.cpp ./Commons/Terminal.cpp ./Commons/Utils.cpp ./demo/main.cpp -o AstraPowerSettings