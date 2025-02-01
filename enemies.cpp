#include "enemies.h"
#include "gameplay.h"
#include "patterns.h"

using namespace std;

// lista przeciwników
vector<Enemy> enemies;

/*
zarządzanie ruchem przeciwników
sekwencja działań dla każdego przeciwnika:
1. sprawdzenie możliwości ruchu
2. zawrócenie jeśli nie można iść dalej
3. ruch do przodu jeśli droga jest wolna
*/
void updateEnemies(vector<string>& maze) {
    for (auto& enemy : enemies) {
        maze[enemy.y][enemy.x] = ' ';  //wyczyść poprzednią pozycję
        
        int nextX = enemy.x;
        int nextY = enemy.y;
        
        //oblicz następny ruch
        if (enemy.goingVertical) {
            if (enemy.goingForward) {
                nextY = enemy.y + 1;  //ruch w dół
            } else {
                nextY = enemy.y - 1;  //ruch w górę
            }
        } else {
            if (enemy.goingForward) {
                nextX = enemy.x + 1;  //ruch w prawo
            } else {
                nextX = enemy.x - 1;  //ruch w lewo
            }
        }
        
        //sprawdź czy można się ruszyć
        if (maze[nextY][nextX] == ' ') {
            enemy.x = nextX;  //wykonaj ruch
            enemy.y = nextY;
        } else {
            enemy.goingForward = !enemy.goingForward;  //zmień kierunek
        }
        
        maze[enemy.y][enemy.x] = '!';  //zaznacz nową pozycję
    }
}

/*
wątek przeciwników
sekwencja działań:
1. poczekaj pół sekundy
2. przesuń przeciwników
3. sprawdź czy gracz nie wpadł na przeciwnika
*/
void enemyMovementThread(vector<string>& maze, bool& gameRunning) {
    while (gameRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        updateEnemies(maze);
        
        //sprawdź zderzenie z graczem
        for (const auto& enemy : enemies) {
            if (enemy.x == player.x && enemy.y == player.y) {
                //znajdź start i przenieś tam gracza
                for (int y = 0; y < MAZE_HEIGHT; y++) {
                    for (int x = 0; x < MAZE_WIDTH; x++) {
                        if (maze[y][x] == '$') {
                            player.x = x + 1;
                            player.y = y;
                            break;
                        }
                    }
                }
            }
        }
    }
} 