#include "Trade.h"

void trade()
{
	srand((unsigned int)time(NULL));

	// ������ ���� (����)
	Item* Acorns = new Item("���丮", 10);
	Acorns->setInfo("�ٶ��㿡�� ���� ���丮");

	Item* Rabbit_Meat = new Item("�䳢���", 10);
	Rabbit_Meat->setInfo("�䳢�κ��� ���� ���");

	// ������ ���� (����)
	Weapon* Wooden_Sword = new Weapon("���", 100, 5);
	Wooden_Sword->setInfo("������ ��� ���� ��");

	Weapon* Bronze_Sword = new Weapon("������", 200, 8);
	Bronze_Sword->setInfo("�߱����� ������ û����");

	Weapon* Sword_of_Iganinja = new Weapon("�̰������ǰ�", 5000, 100);
	Sword_of_Iganinja->setInfo("���� �ϻ��ϱ� ���� ������� ��");
	
	// ������ ���� (����)
	Armor* Lime_Green_Armor = new Armor("���λ����ڿ�", 100, 5);
	Lime_Green_Armor->setInfo("�������� �� �� �ִ� �⺻ �Ƿ�");

	Armor* Taras_Suit = new Armor("Ÿ���ǳ��ڿ�", 3000, 40);
	Taras_Suit->setInfo("�ݰ����� ���� �ܴ����� ���� ����");

	Armor* Skull_Armor = new Armor("�ذ񰩿�", 9000, 90);
	Skull_Armor->setInfo("���鰳�� �ذ��� ¥���� ������� ����");
	
	// �÷��̾� ����
	RPG_Player* player = new RPG_Player("�÷��̾�", 10000);

	// ���� ����
	Merchant* merchant = new Merchant("�����");

	// ������ ������ �ֱ�
	merchant->pushItem(new Item(*Acorns));				// 1,	0
	merchant->pushItem(new Item(*Rabbit_Meat));			// 2,	1
	merchant->pushItem(new Weapon(*Wooden_Sword));		// 3,	0
	merchant->pushItem(new Weapon(*Bronze_Sword));		// 4,	1
	merchant->pushItem(new Weapon(*Sword_of_Iganinja));	// 5,	2
	merchant->pushItem(new Armor(*Lime_Green_Armor));	// 6,	0
	merchant->pushItem(new Armor(*Taras_Suit));			// 7,	1
	merchant->pushItem(new Armor(*Skull_Armor));		// 8,	2

	// Ʈ���̵� ����
	while (1)
	{
		system("cls");
		std::cout << "������ ��: ����ð�..." << std::endl;
		std::cout << "[1] ������ ���" << std::endl;
		std::cout << "[2] ������ �ȱ�" << std::endl;
		std::cout << "[3] (�׽�Ʈ)������ ���" << std::endl;
		std::cout << "[4] (�׽�Ʈ)������ �ȱ�" << std::endl;
		std::string textEnter{ "���ϴ� �ɼ��� �����ϼ���: " };
		int munuSelect{ purchaseInput(textEnter, 1, 4) };

		if (munuSelect == 1) // ������ ����
		{
			while (1)
			{
				system("cls");

				// ���� ��� �����ֱ�
				merchant->printItems();

				// �÷��̾� ���� �����ֱ�
				player->printStatus();

				// �÷��̾� �Է� �ޱ�
				std::string texts[2] = { "������ ������ ��ȣ: ", "������ ������ ����: " };

				int itemListNum{ purchaseInput(texts[0], 0, 8) };
				if (itemListNum == 9999) break;

				// ���� �Ҹ�ǰ�̸� ���� �Է�
				int quantity{ 1 };
				if (itemListNum == 1 || itemListNum == 2)
					quantity = purchaseInput(texts[1], 0, 5000);

				// ������ ����
				if (merchant->getPrice(itemListNum) * quantity <= player->getMoney())
				{
					player->setSeed(merchant->getPrice(itemListNum) * quantity, true);
					player->addItem(merchant->getItem(itemListNum), quantity);
				}
				else
				{
					std::cout << "������ ������ �� ��� �������Դϴ�." << std::endl << std::endl;
					system("pause");
				}
			}
		}
		else if (munuSelect == 2) // ������ �Ǹ�
		{
			while (1)
			{
				// ȭ�� �����
				system("cls");
				std::cout << "������ ��: ���԰��� ���԰��� 75%�� ���شٳ�.." << std::endl;

				// exit
				std::cout << "[0] �ڷΰ���" << std::endl;

				// �κ��丮 �����ֱ�
				player->printInventory();

				// �÷��̾� �Է¹ޱ�
				std::string texts[2] = { "�Ǹ��� ������ ��ȣ: ", "�Ǹ��� ������ ����: " };
				int itemListNum{ purchaseInput(texts[0], 0, 50) };
				if (itemListNum == 9999) break;

				// 2�� �̻��̸� ���� �Է� �ޱ�
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
					std::cout << itemName << "��(��) " << quantity << "�� �Ǹ��Ͽ� "
						<< price << "���� �޾ҽ��ϴ�." << std::endl;

				}
				else
				{
					std::cout << "�κ��丮�� ������ ������ ������� �ʽ��ϴ�." << std::endl;
				}
				system("pause");
			}
			

		}
		// �׽�Ʈ�� ����
		else if (munuSelect == 3)
		{
			system("cls");

			// ���� ��� �����ֱ�
			merchant->printItems();

			// �÷��̾� ���� �����ֱ�
			player->printStatus();

			// �÷��̾� �Է� �ޱ�
			std::string texts[2] = { "������ ������ ��ȣ: ", "������ ������ ����: " };

			int itemListNum{ purchaseInput(texts[0], 0, 8) };
			if (itemListNum == 9999) break;

			merchant->getItem_t(itemListNum);
			//std::cout << merchant->getItem(itemListNum).getName();
			//std::cout << typeid(merchant->getItem_t(itemListNum)).name();
			std::cout << merchant->getItem_t(itemListNum)->getType();
			//system("pause");

			// ���� �Ҹ�ǰ�̸� ���� �Է�
			int quantity{ 1 };
			if (typeid(merchant->getItem_t(itemListNum)) == typeid(Item)) 
				quantity = purchaseInput(texts[1], 0, 5000);


			
		}
		else if (munuSelect == 4)
		{

		}
	}

	std::cout << std::endl;
	std::cout << "������ �������ϴ�.." << std::endl;
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
		// string üũ
		catch (const std::invalid_argument& e)
		{
			std::cout << "[ERROR] '����'�� �ԷµǾ����ϴ�." << std::endl << std::endl;
			continue;
		}

		if (inputNum == "0")
		{
			return 9999;
		}

		// overflow üũ
		if (input < min || input > max)
			std::cout << "[ERROR] ���� �۰ų� Ů�ϴ�." << std::endl << std::endl;
		else
			break;
		
		std::cout << std::endl;
	}

	return input;
}

