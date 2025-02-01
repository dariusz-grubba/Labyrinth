#ifndef MAZE_LEVELS_H
#define MAZE_LEVELS_H

#include <string>
#include "constants.h"

/*
układy wszystkich trzech poziomów. znaczenie symboli:
# = ściana
$ = punkt startowy
@ = wyjście
! = przeciwnik
spacja = puste miejsce, dostępne do poruszania się
*/

// poziom pierwszy
extern const std::string MAZE_LAYOUT[MAZE_HEIGHT];

// poziom drugi
extern const std::string MAZE_LAYOUT_2[MAZE_HEIGHT];

// poziom trzeci
extern const std::string MAZE_LAYOUT_3[MAZE_HEIGHT];

#endif //MAZE_LEVELS_H 