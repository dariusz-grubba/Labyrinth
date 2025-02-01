#include "animations.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "utils.h"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

/*
wyświetlanie tekstu na ekranie z animacją pisania
zwracane wartości:
- true: naciśnięcie esc (wyjście)
- false: naciśnięcie enter (kontynuacja)
*/
bool animateText(const string& filename) {
    //przyciemnienie ekranu
    system("clear");
    sleep_for(milliseconds(50));

    //otwarcia pliku, czyszczenie ekranu, animacja wyświetlania tekstu
    ifstream file(filename);
    system("clear");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
        sleep_for(milliseconds(10));
    }
    file.close();
    
    //oczekiwanie na enter lub esc
    while (true) {
        char key = getch();
        if (key == '\n')
            return false;  //enter = kontynuacja
    }
}