#pragma once

#include "Player_MRPS.h";
#include "RPS_MRPS.h"

void multiRPS();
void rpsBet(MRPS_Player** players, int numOfPlayers, RPS* rps);
void result(MRPS_Player** players, int numOfPlayers, RPS* rps, int& numOfSurv, bool onlyText);
void print(MRPS_Player** players, int numOfPlayers);
