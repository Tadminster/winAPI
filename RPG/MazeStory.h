#pragma once
#include "framework.h"
#include "Player.h"

class MazeStory
{
private:
	bool chapter_1 = false;

public:
	MazeStory();

	void story_1(class RPG_Player* player) const;

	static void		slowPrint(const std::string& sentence, int delay);
	int				player_input(int min, int max) const;
};

