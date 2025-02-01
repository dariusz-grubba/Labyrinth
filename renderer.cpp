#include "renderer.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include "constants.h"
#include "patterns.h"
#include "colors.h"
#include "gameplay.h"

using namespace std;

/*
obliczanie odległości między dwoma punktami
wykorzystywane do określenia stopnia przyciemnienia
obiektów w zależności od odległości od gracza
*/
double getDistance(int x1, int y1, int x2, int y2) {
    int xDiff = x2 - x1;
    int yDiff = y2 - y1;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

/*
rysowanie labiryntu na ekranie
uproszczona implementacja - sekwencyjne rysowanie:
1. tło i ściany
2. gracz i przeciwnicy
3. instrukcje
*/
void drawMaze(const vector<string>& maze, bool fullRedraw) {
    string newFrame = "";
    
    //rysowanie każdego wiersza
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int row = 0; row < 5; row++) {
            newFrame += "    ";
            
            //rysowanie każdej kolumny
            for (int x = 0; x < MAZE_WIDTH; x++) {
                double distance = getDistance(player.x, player.y, x, y);
                
                //weryfikacja maksymalnej odległości
                if (distance > MAX_DISTANCE) {
                    newFrame += "\x1b[38;5;232m        \x1b[0m";
                    continue;
                }

                //weryfikacja zawartości pola i odpowiednie rysowanie
                if (y == player.y && x == player.x) {
                    newFrame += "\x1b[33m" + string(PLAYER_PATTERN[row]) + "\x1b[0m";  //rysowanie gracza
                } 
                else if (maze[y][x] == '#') {
                    newFrame += getWallColor(distance) + string(WALL_PATTERN[row]) + "\x1b[0m";  //rysowanie ściany
                }
                else if (maze[y][x] == '!') {
                    //implementacja mgły wojny dla przeciwników
                    newFrame += getObjectColor(distance, 196) + string(ENEMY_PATTERN[row]) + "\x1b[0m";  //rysowanie przeciwnika
                }
                else if (maze[y][x] == '$') {
                    //implementacja mgły wojny dla punktu startowego
                    newFrame += getObjectColor(distance, 46) + string(START_PATTERN[row]) + "\x1b[0m";  //rysowanie startu
                }
                else if (maze[y][x] == '@') {
                    //implementacja mgły wojny dla wyjścia
                    newFrame += getObjectColor(distance, 171) + string(EXIT_PATTERN[row]) + "\x1b[0m";  //rysowanie wyjścia
                }
                else {
                    if (distance <= VIEW_RADIUS) {
                        newFrame += "        ";  //puste pole w zasięgu wzroku
                    } else {
                        newFrame += getWallColor(distance) + "        " + "\x1b[0m";  //przyciemnione puste pole
                    }
                }
            }
            newFrame += "\n";
        }
    }
    
    //wyświetlanie instrukcji
    newFrame += "\n    Use arrows to move. Find exit (@). Esc = go to menu\n";
    
    //aktualizacja ekranu
    printf("\033[H%s", newFrame.c_str());
}

/*
obsługa wyświetlania w osobnym wątku
realizowane funkcje:
1. wyświetlanie początkowego ekranu gry z animacją
2. ciągła aktualizacja pozycji gracza i przeciwników
3. implementacja efektu mgły wojny
*/
void displayThreadFunction(const vector<string>& maze, const bool& gameRunning) {
    //ukrycie kursora i czyszczenie ekranu
    printf("\033[2J\033[?25l");
    
    //inicjalne wyświetlenie planszy
    drawMaze(maze, true);
    
    //główna pętla wyświetlania
    while (gameRunning) {
        drawMaze(maze);
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_REFRESH));
    }
    
    //przywrócenie kursora
    printf("\033[?25h");
} 