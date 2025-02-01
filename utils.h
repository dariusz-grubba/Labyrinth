#ifndef TEST_MAZE_UTILS_H
#define TEST_MAZE_UTILS_H

#include <unistd.h>

// Make the function inline to avoid multiple definition errors
inline char getch() {
    char buf = 0;
    read(STDIN_FILENO, &buf, 1);
    return buf;
}

// Add the fadeTransition function declaration
void fadeTransition();

#endif //TEST_MAZE_UTILS_H 