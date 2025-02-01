#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include <vector>
#include <string>
#include <thread>

class Game {
public:
    Game(std::vector<std::string>& maze);
    ~Game();
    
    void start();
    void stop();
    bool isRunning() const { return running; }
    
private:
    std::vector<std::string>& maze;
    bool running;
    std::thread enemyThread;
    std::thread displayThread;
    
    void runEnemies();
    void runDisplay();
};

#endif //MAZE_GAME_H 