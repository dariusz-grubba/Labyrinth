#ifndef MAZE_COLORS_H
#define MAZE_COLORS_H

#include <string>

// funkcje kolorowania obiektów
std::string getWallColor(double distance);
std::string getObjectColor(double distance, int baseColor);

#endif //MAZE_COLORS_H 