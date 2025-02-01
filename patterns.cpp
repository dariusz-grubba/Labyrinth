#include "patterns.h"

using namespace std;

//wzór ściany
const string WALL_PATTERN[5] = {
    " ██  ██ ",
    "████████",
    " ██  ██ ",
    "████████",
    " ██  ██ "
};

//wzór gracza
const string PLAYER_PATTERN[5] = {
    "        ",
    "▄ ██ ▄  ",
    " ████   ",
    "▀ ██ ▀  ",
    "        "
};

//wzór punktu startowego
const string START_PATTERN[5] = {
    "▄▄███▄▄·",
    "██      ",
    "███████ ",
    "     ██ ",
    "███████ "
};

//wzór wyjścia
const string EXIT_PATTERN[5] = {
    " ██████ ",
    "██    ██",
    "██ ██ ██",
    "██ ██ ██",
    " █ ████ "
};

//wzór przeciwnika
const string ENEMY_PATTERN[5] = {
    "██████ ",
    "██  ██ ",
    "██  ██ ",
    "██  ██ ",
    "██████ "
}; 