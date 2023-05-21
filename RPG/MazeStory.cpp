#include "MazeStory.h"

MazeStory::MazeStory() = default;

void MazeStory::story_1(class RPG_Player* player) const
{
	std::cout << std::endl;
	// 대사 담기
	const std::string text1[] =
	{
		"\"으... 허리야.. 여..긴 어디지..?\"\n\n",

		"산행에 나섰다 낭떠러지에 떨어졌는데, \n",
		"떨어질 때 충격이 컸는지 잠시 기절한 것 같다. \n",
		"꽤나 깊게 떨어졌는지 사방이 캄캄하다.. \n\n",

		"'툭- 툭- 탁'\n"
		"낭떠러지 위에서 무언가가 떨어지고 있다.\n",
		"[1]살펴본다 [2]무시한다: "
	};


	// 대사를 담은 배열의 크기
	int text_size = std::size(text1);

	// 대사출력
	for (int i = 0; i < text_size; i++)
	{
		if (i == 0)
			slowPrint(text1[i], 150);
		else
			slowPrint(text1[i], 15);
	}


	{
		if (const int temp{ player_input(1,2) };
			temp == 1)
		{
			// 안경선택
			const std::string text2_1[] =
			{
				"\n내가 쓰던 안경이다.\n",
				"\"다행히 부서지지 않았구나..\"\n\n"
				"안경 획득: 시야+1\n\n"
			};
			text_size = std::size(text2_1);
			for (int i = 0; i < text_size; i++)
				slowPrint(text2_1[i], 15);

			player->addItem(new Armor("안경", 100, 0, 1), 1);
		}
		else if (temp == 2)
		{
			// 나뭇가지 선택
			const std::string text2_2[] =
			{
				"\n신경 쓰였지만 애써 무시했다.\n",
				"\"위험은 피하는 게 상책이지\"\n\n",

				"이내 발치에 떨어져 있는 나뭇가지를 발견했다.\n",
				"\"이거라도 들고 있자..\"\n\n",
				"나뭇가지 획득: 공격력+4\n\n"
			};
			text_size = std::size(text2_2);
			for (int i = 0; i < text_size; i++)
				slowPrint(text2_2[i], 15);

			player->addItem(new Weapon("나뭇가지", 100, 0), 1);
			player->setDamage(4, true);
		}
	}

	std::cout << "계속하려면 아무키나 입력하세요." << std::endl;
	_getch();
}

/* 문장을 천천히 출력 (문장, 딜레이시간) */
void MazeStory::slowPrint(const std::string& sentence, int delay)
{
	for (const char c : sentence) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}

int MazeStory::player_input(int min, int max) const
{
	{
		std::string inputNum;
		int input{ 0 };
		while (true)
		{
			std::cin >> inputNum;

			try
			{
				input = std::stoi(inputNum);
			}
			// string 체크
			catch (const std::invalid_argument& e)
			{
				std::cout << "[ERROR] '문자'가 입력되었습니다." << std::endl;
				continue;
			}

			if (inputNum == "0") return 9999;

			// overflow 체크
			if (input < min || input > max)
				std::cout << "[ERROR] 범위안의 값을 입력하십시오." << std::endl;
			else break;

			std::cout << std::endl;
		}

		return input;
	}
}
