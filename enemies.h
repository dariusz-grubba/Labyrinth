#ifndef MAZE_ENEMIES_H
#define MAZE_ENEMIES_H

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "constants.h"

/*
przechowywanie informacji o przeciwnikach:
- x i y: pozycja przeciwnika
- goingvertical: określenie ruchu góra/dół (true) lub lewo/prawo (false)
- goingforward: określenie kierunku w prawo/dół (true) lub w lewo/górę (false)
*/
struct Enemy {
    int x;
    int y;
    bool goingVertical;
    bool goingForward;
};

// lista aktywnych przeciwników na bieżącym poziomie
extern std::vector<Enemy> enemies;

// aktualizacja pozycji przeciwników
void updateEnemies(std::vector<std::string>& maze);

// obsługa wątku przeciwników
void enemyMovementThread(std::vector<std::string>& maze, bool& gameRunning);

#endif //MAZE_ENEMIES_H 