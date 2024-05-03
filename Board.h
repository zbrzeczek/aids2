//
// Created by Zuzanna Brzęczek on 02/05/2024.
//

#ifndef AIDS2_BOARD_H
#define AIDS2_BOARD_H

#include "Stale.h"

class Board {
private:
    int iloscB;
    int iloscR;
    int iloscLinii;
    bool isCorrect;
    int isGameOver;
    bool isPossible;
    char tablicaKonc[MAXSIZE][MAXSIZE];
public:

    Board();

    void wyczyscPlansze();

    int getB();
    int getR();
    int getLinie();
    bool getCorrect();
    int getGameOver();
    bool getPossible();
    char getPole(int y, int x);

    void setB(int B);
    void setR(int R);
    void setLinie(int linie);
    void setCorrect(bool isCorrect);
    void setGameOver(int isGameOver);
    void setPossible(bool isPossible);
    void setPole(char pole, int y, int x);

};


#endif //AIDS2_BOARD_H
