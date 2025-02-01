#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include <string>
#include <vector>

// funkcje rysowania
void drawMaze(const std::vector<std::string>& maze, bool fullRedraw = false);
void displayThreadFunction(const std::vector<std::string>& maze, const bool& gameRunning);
double getDistance(int x1, int y1, int x2, int y2);

#endif //MAZE_RENDERER_H 