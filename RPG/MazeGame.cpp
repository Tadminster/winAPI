#include "framework.h"
#include "MazeGame.h"

void mazeGame(class RPG_Player* player, MazeMap* map, bool bNewGame)
{
	// 난수초기화
	srand(static_cast<unsigned int>(time(nullptr)));

	// 객체 생성
	SaveLoadSystem slSystem("save");					// 세이브 시스템
	auto* maze_story = new MazeStory();					// 스토리
	auto* io_system = new ioSystem();					// 입력

	if (bNewGame)
		maze_story->story_1(player);

	// 게임 플레이
	while (1)
	{
		system("cls");
		
		map->printMap(player);		// 맵 보여주기
		player->printStatus();		// 플레이어 상태 출력
		player->printInventory();	// 인벤토리 출력

		// 방향 입력 받기
		std::cout << std::endl
			<< "[   S   ] 저장하기" << std::endl
			<< "[  ESC  ] 메인메뉴로 돌아가기" << std::endl
			<< "[ ARROW ] 해당 방향으로 이동" << std::endl << std::endl

			<< "움직일 방향을 선택하세요. 이동시엔 SP가 소모됩니다.";
		
		if (int arrow{ io_system->input_arrow_all() }; 
				arrow == 0)
		{
			slSystem.saveGame("savegame.bin", player, map);
			continue;
		} 
		else if (arrow == 999)
		{
			std::string mainMenus[] = 
			{
				"메인 화면으로 돌아가시겠습니까?",
				"[ 확인 ]",
				"[ 취소 ]" 
			};
			constexpr int arr_size{ std::size(mainMenus) };
			if (int menu_select{ io_system->input_arrow_col(mainMenus, arr_size) };
				menu_select == 1)
				break;
			else continue;
		}
		else
		{ 
			// 입력받은 방향으로 이동
			std::string nextRoom;
			nextRoom = player->movePlayer(map, arrow);
			
			// RoomEvent 시작
			map->startMapEvent(nextRoom, player);

		}
		
		// 플레이어 사망여부 체크
		if (player->getHp() == 0)
		{
			std::cout << "플레이어가 사망했습니다.." << std::endl;
			std::cout << "계속하려면 아무키나 입력하세요." << std::endl;
			(void) _getch();
		}
	}
}	