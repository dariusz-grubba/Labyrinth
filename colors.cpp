#include "colors.h"
#include "constants.h"

using namespace std;

/*
określanie koloru dla ścian
stopniowe przyciemnianie w zależności od odległości
całkowite przyciemnienie po przekroczeniu maksymalnej odległości
*/
string getWallColor(double distance) {
    if (distance >= MAX_DISTANCE || distance >= VIEW_RADIUS) {
        return "\x1b[38;5;232m";  //kolor czarny
    }
    else if (distance > VIEW_RADIUS * 0.75) {
        return "\x1b[38;5;240m";  //bardzo ciemny
    }
    else if (distance > VIEW_RADIUS * 0.5) {
        return "\x1b[38;5;245m";  //ciemny
    }
    else if (distance > VIEW_RADIUS * 0.25) {
        return "\x1b[38;5;250m";  //jasny
    }
    else {
        return "\x1b[38;5;255m";  //bardzo jasny
    }
}

/*
określanie kolorów dla obiektów w grze
przyciemnianie obiektów bazując na odległości od gracza
przypisane kolory dla obiektów:
- przeciwnicy: czerwony (basecolor 196)
- punkt startowy: zielony (basecolor 46)
- wyjście: fioletowy (basecolor 171)
*/
string getObjectColor(double distance, int baseColor) {
    if (distance >= MAX_DISTANCE) {
        return "\x1b[38;5;232m";
    }
    
    //0 = obiekt jest przy graczu
    //1 = obiekt jest na granicy widoczności
    double ratio = distance / VIEW_RADIUS; 
    int darkness = ratio * 23;   
    
    //przeciwnik (czerwony)
    if (baseColor == 196) {
        if (darkness < 4)
            return "\x1b[1;31m";          //bardzo jasny czerwony
        else if (darkness < 8)
            return "\x1b[38;5;160m";  //jasny czerwony
        else if (darkness < 12)
            return "\x1b[38;5;124m"; //normalny czerwony
        else if (darkness < 16)
            return "\x1b[38;5;88m";  //ciemny czerwony
        else if (darkness < 20)
            return "\x1b[38;5;52m";  //bardzo ciemny czerwony
        else if (darkness < 22)
            return "\x1b[38;5;233m"; //prawie czarny
        else
            return "\x1b[38;5;232m";                    //czarny
    }
    
    //start (zielony)
    if (baseColor == 46) {
        if (darkness < 4)
            return "\x1b[38;5;46m";       //bardzo jasny zielony
        else if (darkness < 8)
            return "\x1b[38;5;40m";   //jasny zielony
        else if (darkness < 12)
            return "\x1b[38;5;34m";  //normalny zielony
        else if (darkness < 16)
            return "\x1b[38;5;28m";  //ciemny zielony
        else if (darkness < 20)
            return "\x1b[38;5;22m";  //bardzo ciemny zielony
        else if (darkness < 22)
            return "\x1b[38;5;233m"; //prawie czarny
        else
            return "\x1b[38;5;232m";                    //czarny
    }
    
    //wyjście (fioletowy)
    if (baseColor == 171) {
        if (darkness < 4)
            return "\x1b[38;5;171m";      //bardzo jasny fioletowy
        else if (darkness < 8)
            return "\x1b[38;5;165m";  //jasny fioletowy
        else if (darkness < 12)
            return "\x1b[38;5;127m"; //normalny fioletowy
        else if (darkness < 16)
            return "\x1b[38;5;91m";  //ciemny fioletowy
        else if (darkness < 20)
            return "\x1b[38;5;55m";  //bardzo ciemny fioletowy
        else if (darkness < 22)
            return "\x1b[38;5;233m"; //prawie czarny
        else
            return "\x1b[38;5;232m";                    //czarny
    }
    
    return "\x1b[38;5;255m"; //domyślnie - biały
} 