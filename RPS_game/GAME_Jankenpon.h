#pragma once
#include "Player_Jankenpon.h"

void jankenpon();
void playerBet(JKP_Player** players, bool isFirst);
void firstRound(JKP_Player** players, int result);
void secondRound(JKP_Player* attacker, JKP_Player* defender, int result);