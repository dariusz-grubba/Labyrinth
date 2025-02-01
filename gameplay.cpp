#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include "utils.h"
#include <sys/select.h>
#include "enemies.h"
#include "constants.h"
#include "levels.h"
#include "patterns.h"
#include "colors.h"
#include "animations.h"
#include "renderer.h"

using namespace std;

/*
śledzenie pozycji w labiryncie
wykorzystywane do pozycji gracza
*/
struct Position {
    int x;
    int y;
} player;

/*
główna funkcja rozgrywki, realizująca:
1. wczytywanie poziomów
2. inicjalizację przeciwników i gracza
3. obsługę ruchu gracza
4. weryfikację warunków wygranej/przegranej
5. wyświetlanie komunikatów o ukończeniu poziomów
*/
void gameplay() {
    //inicjalizacja pierwszego poziomu
    vector<string> currentLevel(MAZE_LAYOUT, MAZE_LAYOUT + MAZE_HEIGHT);
    
    //iteracja przez poziomy
    for (int levelNumber = 1; levelNumber <= 3; levelNumber++) {
        //konfiguracja ekranu
        system("clear");
        printf("\033[2J\033[H\033[?25l");
        
        //inicjalizacja poziomu
        vector<string> maze = currentLevel;
        enemies.clear();
        
        //detekcja przeciwników i gracza
        for (int y = 0; y < MAZE_HEIGHT; y++) {
            for (int x = 0; x < MAZE_WIDTH; x++) {
                if (maze[y][x] == '!') {
                    //inicjalizacja przeciwnika
                    bool ruchPionowy = (maze[y-1][x] == ' ' || maze[y+1][x] == ' ');
                    enemies.push_back({x, y, ruchPionowy, true});
                }
                else if (maze[y][x] == '$') {
                    //inicjalizacja gracza
                    player.x = x + 1;
                    player.y = y;
                }
            }
        }
        
        //uruchomienie wątków gry
        bool gameRunning = true;
        std::thread enemyThread(enemyMovementThread, std::ref(maze), std::ref(gameRunning));
        std::thread displayThread(displayThreadFunction, std::ref(maze), std::ref(gameRunning));
        
        //główna pętla gry
        while (true) {
            //weryfikacja kolizji z przeciwnikiem
            if (maze[player.y][player.x] == '!') {
                //powrót na pozycję startową
                for (int y = 0; y < MAZE_HEIGHT; y++) {
                    for (int x = 0; x < MAZE_WIDTH; x++) {
                        if (maze[y][x] == '$') {
                            player = {x + 1, y};
                            break;
                        }
                    }
                }
            }

            //zapamiętanie poprzedniej pozycji
            Position oldPos = player;
            
            //obsługa ruchu gracza
            char key = getch();
            if (key == 27) {
                //weryfikacja typu klawisza (esc lub strzałka)
                struct timeval tv = {0L, 100000L};
                fd_set fds;
                FD_ZERO(&fds);
                FD_SET(STDIN_FILENO, &fds);
                
                if (select(1, &fds, NULL, NULL, &tv) == 0) {
                    //zakończenie gry
                    gameRunning = false;
                    enemyThread.join();
                    displayThread.join();
                    return;
                }
                
                //implementacja ruchu strzałkami
                char next[2];
                read(STDIN_FILENO, next, 2);
                if (next[1] == 'A') player.y--;        // ruch w górę
                else if (next[1] == 'B') player.y++;   // ruch w dół
                else if (next[1] == 'C') player.x++;   // ruch w prawo
                else if (next[1] == 'D') player.x--;   // ruch w lewo
            }
            
            //weryfikacja kolizji ze ścianą
            if (maze[player.y][player.x] == '#') {
                player = oldPos;
            }
            
            //weryfikacja dotarcia do wyjścia
            if (maze[player.y][player.x] == '@') {
                gameRunning = false;
                enemyThread.join();
                displayThread.join();
                
                //wyświetlanie komunikatu końcowego
                const string levelMessages[] = {
                    "/Users/device/CLionProjects/test_maze/menu/level1_complete.txt",
                    "/Users/device/CLionProjects/test_maze/menu/level2_complete.txt",
                    "/Users/device/CLionProjects/test_maze/menu/game_complete.txt"
                };
                
                if (animateText(levelMessages[levelNumber - 1])) return;
                
                // przejście do następnego poziomu
                if (levelNumber == 1) {
                    currentLevel = vector<string>(MAZE_LAYOUT_2, MAZE_LAYOUT_2 + MAZE_HEIGHT);
                } else if (levelNumber == 2) {
                    currentLevel = vector<string>(MAZE_LAYOUT_3, MAZE_LAYOUT_3 + MAZE_HEIGHT);
                }
                break;
            }
        }
    }
    
    //przywrócenie widoczności kursora
    printf("\033[?25h");
} 