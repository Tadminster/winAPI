#pragma once

#include "Player_MinusOne.h";
#include "RPS_MinusOne.h"

void minusOne();
void rpsBet(MO_Player** players, int numOfPlayers);
void print(MO_Player** players, int numOfPlayers, bool Mulligan);
void selectOne(MO_Player** players, int numOfPlayers, RPS_MinusOne* rps);
void result(MO_Player** players, int numOfPlayers, RPS_MinusOne* rps, int& numOfSurv, bool onlyText);
