#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "utils.h"
#include "animations.h"

using namespace std;
namespace fs = std::filesystem;

/*
zarządzanie ustawieniami terminala
funkcjonalności:
1. odczyt klawiszy bez oczekiwania na enter
2. ukrycie wprowadzanych znaków
3. przywracanie standardowych ustawień po zakończeniu
*/
void configureTerminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restoreTerminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void gameplay();

/*
główna funkcja menu, realizująca:
1. wyświetlanie opcji menu (graj, autorzy, wyjście)
2. obsługę wyboru opcji strzałkami
3. przetwarzanie wyboru gracza
4. wyświetlanie ekranów wprowadzających przed rozpoczęciem gry
*/
int main() {
    //konfiguracja terminala dla gry
    configureTerminal();
    
    //definicja plików menu
    string menuFiles[] = {
        "/Users/device/CLionProjects/test_maze/menu/play-selected.txt",
        "/Users/device/CLionProjects/test_maze/menu/credits-selected.txt",
        "/Users/device/CLionProjects/test_maze/menu/quit-selected.txt"
    };
    
    //śledzenie aktualnie wybranej opcji
    int selectedOption = 0;  // 0=graj, 1=autorzy, 2=wyjście
    bool keepRunning = true;
    
    //główna pętla menu
    while (keepRunning) {
        //czyszczenie ekranu
        system("clear");
        printf("\033[2J\033[H");
        
        //wyświetlenie menu (weryfikacja czy plik istnieje)
        ifstream menuFile(menuFiles[selectedOption]);
        if (!menuFile.is_open()) {
            printf("\x1b[31m błąd: nie można otworzyć pliku menu \x1b[0m\n");
            restoreTerminal();
            return 1;
        }
        
        //wyświetlanie menu
        string line;
        while (getline(menuFile, line)) {
            printf("\x1b[37m%s\x1b[0m\n", line.c_str());
        }
        menuFile.close();
        
        //oczekiwanie na input gracza
        char key = getch();
        
        //obsługa nawigacji strzałkami
        if (key == 27) {
            getch();
            key = getch();
            
            //obsługa strzałki w górę
            if (key == 65) {
                if (selectedOption == 0) {
                    selectedOption = 2;
                } else {
                    selectedOption = selectedOption - 1;
                }
            }
            //obsługa strzałki w dół
            else if (key == 66) {
                if (selectedOption == 2) {
                    selectedOption = 0;
                } else {
                    selectedOption = selectedOption + 1;
                }
            }
        }
        //obsługa klawisza enter
        else if (key == '\n') {
            //wybór opcji graj
            if (selectedOption == 0) {
                //wyświetlanie ekranów wprowadzających
                string introFiles[] = {
                    "/Users/device/CLionProjects/test_maze/menu/first.txt",
                    "/Users/device/CLionProjects/test_maze/menu/second.txt",
                    "/Users/device/CLionProjects/test_maze/menu/third.txt"
                };
                
                //iteracja przez ekrany wprowadzające
                for (string introFile : introFiles) {
                    //czyszczenie ekranu
                    system("clear");
                    printf("\033[2J\033[H");
                    
                    //wyświetlenie ekranu wprowadzającego
                    ifstream intro(introFile);
                    if (!intro.is_open()) {
                        printf("\x1b[31m błąd: nie można otworzyć pliku wprowadzenia \x1b[0m\n");
                        sleep(2);
                        continue;
                    }
                    
                    //animacja wyświetlania tekstu
                    while (getline(intro, line)) {
                        printf("%s\n", line.c_str());
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        fflush(stdout);
                    }
                    intro.close();
                    
                    //oczekiwanie na enter
                    while (getch() != '\n');
                }
                
                //rozpoczęcie rozgrywki
                gameplay();
            }
            //wybór opcji credits
            else if (selectedOption == 1) {
                //czyszczenie ekranu
                system("clear");
                printf("\033[2J\033[H");
                
                //wyświetlanie informacji o creditsach
                ifstream credits("/Users/device/CLionProjects/test_maze/menu/credits-section.txt");
                while (getline(credits, line)) {
                    printf("\x1b[37m%s\x1b[0m\n", line.c_str());
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    fflush(stdout);
                }
                credits.close();
                
                //oczekiwanie na input
                getch();
            }
            //wybór opcji wyjście
            else if (selectedOption == 2) {
                keepRunning = false;
                restoreTerminal();
                system("osascript /Users/device/CLionProjects/test_maze/quit-app.scpt");
                return 0;
            }
        }
    }
    
    //przywrócenie terminala do normalnego stanu i zakończenie
    restoreTerminal();
    return 0;
}

