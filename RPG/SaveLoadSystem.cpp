#include "SaveLoadSystem.h"

SaveLoadSystem::SaveLoadSystem(const std::string& savePath) : savePath(savePath) {}

/* 게임 저장하기 (파일명, 플레이어, 맵) */
void SaveLoadSystem::saveGame(const std::string& fileName, class RPG_Player* player, class MazeMap* map)
{
	// 폴더 설정
	std::filesystem::path saveDirectory(this->savePath);
	if (!std::filesystem::exists(saveDirectory)) 
		std::filesystem::create_directory(saveDirectory);

	// 경로 설정
	std::string filePath = this->savePath + "/" + fileName;
	std::ofstream outFile(filePath, std::ios::out | std::ios::binary);

	if (outFile.is_open())
	{
		// 플레이어 스탯 저장
		outFile << "PLAYER_HP " << player->getHp() << std::endl;
		outFile << "PLAYER_SP " << player->getSp() << std::endl;
		outFile << "PLAYER_GOLD " << player->getMoney() << std::endl;
		outFile << "PLAYER_LOCA " << player->getLocation(0) << " " << player->getLocation(1) << std::endl;

		// 맵 저장
		for (int i = 0; i < map->getMapSize(0); i++)
		{
			for (int j = 0; j < map->getMapSize(1); j++)
				outFile << map->getMap(i, j) << " ";
			outFile << std::endl;
		}

		// 아이템 저장
		player->saveInventory(outFile);

		outFile.close();
		std::cout << "게임 저장 완료" << std::endl;
		system("pause");
	}
	else
	{
		std::cerr << "Error: 게임 저장 실패" << std::endl;
		system("pause");
	}

}

bool SaveLoadSystem::loadGame(const std::string& fileName, class RPG_Player* player, class MazeMap* map)
{
	std::string filePath = this->savePath + "/" + fileName;
	std::ifstream inFile(filePath, std::ios::binary);
	if (inFile.is_open()) 
	{

		std::string tempStr;
		int tempValue[2];
		// PLAYER_HP > PLAYER_SP > PLAYER_GOLD > PLAYER_LOCATION > MAP_COL < MAP_ROW
		inFile >> tempStr >> tempValue[0];
		player->setHp(tempValue[0], 0);

		inFile >> tempStr >> tempValue[0];
		player->setSp(tempValue[0], 0);

		inFile >> tempStr >> tempValue[0];
		player->setMoney(tempValue[0], 0);

		inFile >> tempStr >> tempValue[0] >> tempValue[1];
		player->setLocation(tempValue[0], tempValue[1]);

		for (int i = 0; i < map->getMapSize(0); i++)
		{
			for (int j = 0; j < map->getMapSize(1); j++)
			{
				inFile >> tempStr;
				map->setMapElement(i, j, tempStr);
			}
		}

		player->loadInventoty(inFile);

		inFile.close();
		std::cout << "게임 불러오기 완료" << std::endl;
		system("pause");
		return true;
	}
	else 
	{
		std::cerr 
			<< "Error: 게임 불러오기 실패" << std::endl
			<< "저장된 내역이 없습니다." << std::endl;
		system("pause");
		return false;
	}
}
