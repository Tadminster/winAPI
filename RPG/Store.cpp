#include "Trade.h"

void trade()
{
	srand((unsigned int)time(NULL));

	// 아이템 생성 (잡템)
	Item* Acorns = new Item("도토리", 10);
	Acorns->setInfo("다람쥐에게 뺏은 도토리");

	Item* Rabbit_Meat = new Item("토끼고기", 10);
	Rabbit_Meat->setInfo("토끼로부터 얻은 고기");

	// 아이템 생성 (무기)
	Weapon* Wooden_Sword = new Weapon("목검", 100, 5);
	Wooden_Sword->setInfo("나무를 깎아 만든 검");

	Weapon* Bronze_Sword = new Weapon("도씨검", 200, 8);
	Bronze_Sword->setInfo("중국에서 전래된 청동검");

	Weapon* Sword_of_Iganinja = new Weapon("이가닌자의검", 5000, 100);
	Sword_of_Iganinja->setInfo("적을 암살하기 위해 만들어진 검");
	
	// 아이템 생성 (갑옷)
	Armor* Lime_Green_Armor = new Armor("연두색남자옷", 100, 5);
	Lime_Green_Armor->setInfo("상점에서 살 수 있는 기본 의류");

	Armor* Taras_Suit = new Armor("타라의남자옷", 3000, 40);
	Taras_Suit->setInfo("금강석과 같은 단단함을 지닌 갑주");

	Armor* Skull_Armor = new Armor("해골갑옷", 9000, 90);
	Skull_Armor->setInfo("수백개의 해골을 짜맞춰 만들어진 갑옷");
	
	// 플레이어 생성
	RPG_Player* player = new RPG_Player("플레이어", 10000);

	// 상인 생성
	Merchant* merchant = new Merchant("잡상인");

	// 상점에 아이템 넣기
	merchant->pushItem(new Item(*Acorns));				// 1,	0
	merchant->pushItem(new Item(*Rabbit_Meat));			// 2,	1
	merchant->pushItem(new Weapon(*Wooden_Sword));		// 3,	0
	merchant->pushItem(new Weapon(*Bronze_Sword));		// 4,	1
	merchant->pushItem(new Weapon(*Sword_of_Iganinja));	// 5,	2
	merchant->pushItem(new Armor(*Lime_Green_Armor));	// 6,	0
	merchant->pushItem(new Armor(*Taras_Suit));			// 7,	1
	merchant->pushItem(new Armor(*Skull_Armor));		// 8,	2

	// 트레이드 시작
	while (1)
	{
		system("cls");
		std::cout << "상인의 말: 어서오시게..." << std::endl;
		std::cout << "[1] 아이템 사기" << std::endl;
		std::cout << "[2] 아이템 팔기" << std::endl;
		std::cout << "[3] (테스트)아이템 사기" << std::endl;
		std::cout << "[4] (테스트)아이템 팔기" << std::endl;
		std::string textEnter{ "원하는 옵션을 선택하세요: " };
		int munuSelect{ purchaseInput(textEnter, 1, 4) };

		if (munuSelect == 1) // 아이템 구입
		{
			while (1)
			{
				system("cls");

				// 상점 목록 보여주기
				merchant->printItems();

				// 플레이어 상태 보여주기
				player->printStatus();

				// 플레이어 입력 받기
				std::string texts[2] = { "구입할 아이템 번호: ", "구입할 아이템 수량: " };

				int itemListNum{ purchaseInput(texts[0], 0, 8) };
				if (itemListNum == 9999) break;

				// 만약 소모품이면 수량 입력
				int quantity{ 1 };
				if (itemListNum == 1 || itemListNum == 2)
					quantity = purchaseInput(texts[1], 0, 5000);

				// 아이템 구입
				if (merchant->getPrice(itemListNum) * quantity <= player->getMoney())
				{
					player->setSeed(merchant->getPrice(itemListNum) * quantity, true);
					player->addItem(merchant->getItem(itemListNum), quantity);
				}
				else
				{
					std::cout << "소유한 돈보다 더 비싼 아이템입니다." << std::endl << std::endl;
					system("pause");
				}
			}
		}
		else if (munuSelect == 2) // 아이템 판매
		{
			while (1)
			{
				// 화면 지우기
				system("cls");
				std::cout << "상인의 말: 매입가는 구입가의 75%만 쳐준다네.." << std::endl;

				// exit
				std::cout << "[0] 뒤로가기" << std::endl;

				// 인벤토리 보여주기
				player->printInventory();

				// 플레이어 입력받기
				std::string texts[2] = { "판매할 아이템 번호: ", "판매할 아이템 수량: " };
				int itemListNum{ purchaseInput(texts[0], 0, 50) };
				if (itemListNum == 9999) break;

				// 2개 이상이면 수량 입력 받기
				int quantity{ 1 };
				if (player->getItemQuantity(itemName) > 1)
				{
					quantity = purchaseInput(texts[1], 0, 5000);
				}

				if (player->getItemQuantity(itemName) >= quantity)
				{
					int price{ static_cast<int>((merchant->getPrice(itemName)) * quantity * 0.75) };
					player->setSeed( price, false);
					player->removeItem(itemName, quantity);
					std::cout << itemName << "을(를) " << quantity << "개 판매하여 "
						<< price << "원을 받았습니다." << std::endl;

				}
				else
				{
					std::cout << "인벤토리에 아이템 개수가 충분하지 않습니다." << std::endl;
				}
				system("pause");
			}
			

		}
		// 테스트용 구매
		else if (munuSelect == 3)
		{
			system("cls");

			// 상점 목록 보여주기
			merchant->printItems();

			// 플레이어 상태 보여주기
			player->printStatus();

			// 플레이어 입력 받기
			std::string texts[2] = { "구입할 아이템 번호: ", "구입할 아이템 수량: " };

			int itemListNum{ purchaseInput(texts[0], 0, 8) };
			if (itemListNum == 9999) break;

			merchant->getItem_t(itemListNum);
			//std::cout << merchant->getItem(itemListNum).getName();
			//std::cout << typeid(merchant->getItem_t(itemListNum)).name();
			std::cout << merchant->getItem_t(itemListNum)->getType();
			//system("pause");

			// 만약 소모품이면 수량 입력
			int quantity{ 1 };
			if (typeid(merchant->getItem_t(itemListNum)) == typeid(Item)) 
				quantity = purchaseInput(texts[1], 0, 5000);


			
		}
		else if (munuSelect == 4)
		{

		}
	}

	std::cout << std::endl;
	std::cout << "상점을 나갔습니다.." << std::endl;
	system("pause");
	system("cls");

	delete player;
	delete merchant;
}

int purchaseInput(std::string text, int min, int max)
{
	std::string inputNum;
	int input{ 0 };
	while (1)
	{
		std::cout << text;
		std::cin >> inputNum;

		try
		{
			input = std::stoi(inputNum);
		}
		// string 체크
		catch (const std::invalid_argument& e)
		{
			std::cout << "[ERROR] '문자'가 입력되었습니다." << std::endl << std::endl;
			continue;
		}

		if (inputNum == "0")
		{
			return 9999;
		}

		// overflow 체크
		if (input < min || input > max)
			std::cout << "[ERROR] 값이 작거나 큽니다." << std::endl << std::endl;
		else
			break;
		
		std::cout << std::endl;
	}

	return input;
}

