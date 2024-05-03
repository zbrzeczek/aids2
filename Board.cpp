//
// Created by Zuzanna Brzęczek on 02/05/2024.
//

#include "Board.h"

Board::Board() {

    iloscLinii = 0;
    iloscR = 0;
    iloscB = 0;
    isCorrect = false;
    isGameOver = 0;
    isPossible = false;


    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            setPole(' ', i, j);
        }
    }
}

void Board::wyczyscPlansze() {

    isCorrect = false;
    isGameOver = 0;
    isPossible = false;
    iloscLinii = 0;
    iloscR = 0;
    iloscB = 0;

    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            setPole(' ', i, j);
        }
    }
}

void Board::setB(int B) {
    iloscB = B;
}

void Board::setR(int R) {
    iloscR = R;
}

void Board::setLinie(int linie) {
    iloscLinii = linie;
}

void Board::setPole(char pole, int y, int x) {
    tablicaKonc[y][x] = pole;
}

void Board::setPossible(bool isPossible) {
    this->isPossible = isPossible;
}

void Board::setGameOver(int isGameOver) {
    this->isGameOver = isGameOver;
}

void Board::setCorrect(bool isCorrect) {
    this->isCorrect = isCorrect;
}



//getery
int Board::getB() {
    return iloscB;
}
int Board::getR() {
    return iloscR;
}
int Board::getLinie() {
    return iloscLinii;
}

char Board::getPole(int y, int x) {
    return tablicaKonc[y][x];
}

bool Board::getPossible() {
    return isPossible;
}

int Board::getGameOver() {
    return isGameOver;
}

bool Board::getCorrect() {
    return isCorrect;
}