#include "Trade.h"
#include "MazeGame.h"
#include "SaveLoadSystem.h"

int main()
{

	MazeMap* map = new MazeMap(16, 15);			// 맵
	RPG_Player* player = new RPG_Player();		// 플레이어
	SaveLoadSystem slSystem("save");			// 세이브, 로드
	ioSystem iosystem;

	std::string mainMenus[] = {
		"미 로  게 임",
		"[ 처음부터 ]",
		"[ 불러오기 ]",
		"[ 종료하기 ]" };
	constexpr int arr_size{ std::size(mainMenus)};

	while (1)
	{
		iosystem.output_img_main();
		int menu_select{ iosystem.input_arrow_col(mainMenus, arr_size) };

		system("cls");
		
		if (menu_select == 1)
		{
			map->createMap();
			mazeGame(player, map, true);
		}
		else if (menu_select == 2)
		{
			if (slSystem.loadGame("savegame.bin", player, map))
			{ 
				SaveLoadSystem slSystem("save");						// 세이브 시스템
				mazeGame(player, map, false);
			}
		}
		else if (menu_select == 3)
			break;
		else 
			std::cout << "올바른 옵션을 선택하세요." << std::endl;
	}

	delete map;
	delete player;
	exit(1);
}
