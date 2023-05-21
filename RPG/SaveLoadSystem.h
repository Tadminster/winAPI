#pragma once
#include <filesystem>
#include <fstream>


#include "framework.h"
#include "Player.h"
#include "MazeMap.h"


class SaveLoadSystem
{
private:
	std::string savePath;

public:
	SaveLoadSystem(const std::string& savePath);

	void saveGame(const std::string& fileName, class RPG_Player* player, class MazeMap* map);
	bool loadGame(const std::string& fileName, class RPG_Player* player, class MazeMap* map);
};

