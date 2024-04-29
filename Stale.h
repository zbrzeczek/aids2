//
// Created by Zuzanna Brzęczek on 15/04/2024.
//

#ifndef AIDS2_STALE_H
#define AIDS2_STALE_H

#include <string>
using namespace std;

struct Point{
    int x;
    int y;
};

#define MAXSIZE 11
#define BLUE 2
#define RED 1

const string sizeString = "BOARD_SIZE";
const string pNumString = "PAWNS_NUMBER";
const string bCorrectString = "IS_BOARD_CORRECT";
const string gameOverString = "IS_GAME_OVER";
const string bPossibleString = "IS_BOARD_POSSIBLE";
const string red1NaiveString = "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
const string blue1NaiveString = "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
const string red2NaiveString = "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
const string blue2NaiveString = "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
const string red1PerfectString = "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
const string blue1PerfectString = "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
const string red2PerfectString = "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";
const string blue2PerfectString = "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";


#endif //AIDS2_STALE_H
