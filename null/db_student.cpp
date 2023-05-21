#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Student
{
private:
	std::string name;
	int age;
	int sex;

public:
	Student(std::string name, int age, int sex, int index)
	{
		this->name = name;
		this->age = age;
		this->sex = sex;
	}

	void setName(std::string name)
	{
		this->name = name;
	}
	std::string getName()
	{
		return this->name;
	}

	void setAge(int age)
	{
		this->age = age;
	}
	int getAge()
	{
		return this->age;
	}

	void setSex(int sex)
	{
		this->sex = sex;
	}
	int getSex()
	{
		return this->sex;
	}

	void print(int index)
	{
		std::cout
			<< "[" << index << "]\t"
			<< this->name << "\t"
			<< this->age << "\t";
		if (this->sex % 2 == 1) std::cout << "����";
		else if (this->sex % 2 == 0) std::cout << "����";
		std::cout << std::endl;
	}
};


void addStudent(std::vector<Student*>& student);
int intInput(int min, int max, std::string& text);
void printAll(std::vector<Student*> student);
void deleteAll(std::vector<Student*>& student);
void search(std::vector<Student*>& student, int type);
void deleteElement(std::vector<Student*>& student, std::vector<int>& tempNum);
void bubbleSort(std::vector<Student*>& student, bool bName, bool bAge, bool bForward);

int main()
{
	// ���� ��������, ��������
	bool bForward = true;
	bool bSortArrow = false;

	// Student ���� ����
	std::vector<Student*> student;

	// �л� ��Ϻ� ����
	while (1)
	{
		std::cout << "�л� ��Ϻ�" << std::endl;
		std::cout << "[1] �л� �߰��ϱ�" << std::endl;
		std::cout << "[2] �л� �����ϱ�" << std::endl;
		std::cout << "[3] �л� �����ϱ�" << std::endl;

		std::cout << "���ϴ� �ɼ��� �����ϼ���: ";
		std::string input;

		// ���Ĺ��� ����� �ٷ� �Ѿ��
		if (bSortArrow)
		{
			std::cout << "3" << std::endl;
			input = "3";
			bSortArrow = false;
		} 
		else
			std::cin >> input;

		if (input == "1")
		{
			addStudent(student);
			system("cls");
			printAll(student);
		}
		else if (input == "2")
		{
			std::cout << std::endl;
			std::cout << "[1] �̸����� ã��" << std::endl;
			std::cout << "[2] ���̷� ã��" << std::endl;
			std::cout << "���ϴ� �ɼ��� �����ϼ���: ";
			std::cin >> input;

			if (input == "1")
				search(student, 0);
			else if (input == "2")
				search(student, 1);
		}
		else if (input == "3")
		{
			std::cout << std::endl;
			if (bForward)
				std::cout << "[0] ���Ĺ��� ����: ���� ��������" << std::endl;
			else 
				std::cout << "[0] ���Ĺ��� ����: ���� ��������" << std::endl;
			std::cout << "[1] �̸� ������ ����" << std::endl;
			std::cout << "[2] ���� ������ ����" << std::endl;
			std::cout << "���ϴ� �ɼ��� �����ϼ���: ";
			std::cin >> input;

			if (input == "1")
				bubbleSort(student, true, false, bForward);
			else if (input == "2")
				bubbleSort(student, false, true, bForward);
			else if (input == "0")
			{
				bForward = !bForward;
				bSortArrow = true;
				system("cls");
			}
		}
		else
		{
			std::cout << "[!] �߸��� �Է�" << std::endl << std::endl;
			system("pause");
			system("cls");
		}
	}

	deleteAll(student);
}

void addStudent(std::vector<Student*>& student)
{
	std::cout << std::endl;
	std::cout << "�̸��� �Է��ϼ���: ";
	std::string name;
	std::cin >> name;

	std::string textAge = "���̸� �Է��ϼ���: ";
	int age{ intInput(0, 99, textAge) };

	std::cout << "¦���� ����, Ȧ���� ����" << std::endl;
	std::string textSex = "������ �Է��ϼ���: ";
	int sex{ intInput(0, 99, textSex) };

	Student* newStudent = new Student(name, age, sex, student.size());
	/*newStudent->setName(name);
	newStudent->setAge(age);
	newStudent->setSex(sex);*/

	student.push_back(newStudent);
}

/* �÷��̾� �Է� */
int intInput(int min, int max, std::string& text)
{
	std::string str;
	int input{ 0 };
	while (1)
	{
		std::cout << text;
		std::cin >> str;

		try
		{
			input = std::stoi(str);
		}
		// string checking
		catch (const std::invalid_argument& e)
		{
			std::cout << "[!] '����'�� �ԷµǾ����ϴ�." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < min || input > max)
			std::cout << "[!] '��'�� �۰ų� Ů�ϴ�." << std::endl;
		else break;
		std::cout << std::endl;
	}

	return input;
}


void printAll(std::vector<Student*> student)
{
	std::cout << "\t�̸�\t����\t����" << std::endl;
	for (int i = 0; i < student.size(); i++)
		student[i]->print(i);
	std::cout << std::endl << "-----------------------------" << std::endl;
	std::cout << std::endl;
}

void deleteAll(std::vector<Student*>& student)
{
	for (Student* s : student)
		delete s;
}

void search(std::vector<Student*>& student, int type)
{
	std::vector<int> tempNum;

	system("cls");
	printAll(student);

	std::cout << std::endl;
	//type == 0 �̸����� �˻�, type == 1 ���̷� �˻�
	if (type == 0)
		std::cout << "ã�� �̸� �˻�: ";
	else if (type == 1)
		std::cout << "ã�� ���� �˻�: ";

	// ���ڿ� �Է¹ް�
	std::string tempStr;
	std::cin >> tempStr;

	// ���Խ� ���Ͽ� �߰��ϰ�
	std::regex pattern(tempStr);


	system("cls");
	std::cout << "\t�̸�\t����\t����" << std::endl;
	for (int i = 0; i < student.size(); i++)
	{

		// ��� �ؽ�Ʈ ����
		std::string targetStr;
		if (type == 0)
			targetStr = student[i]->getName();
		else if (type == 1)
			targetStr = std::to_string(student[i]->getAge());

		// ����ã���� ��� & tempNum�� push_back
		if (regex_match(targetStr, pattern))
		{
			student[i]->print(i);
			tempNum.push_back(i);
		}
	}
	std::cout << std::endl << "-----------------------------" << std::endl;

	deleteElement(student, tempNum);
}

void deleteElement(std::vector<Student*>& student, std::vector<int>& tempNum)
{
	std::cout << std::endl;
	std::string textDelete = "������ ��ȣ �Է�: ";
	int num{ intInput(0, 99, textDelete) };

	bool isThere = false;
	for (auto& n : tempNum)
	{
		if (n == num)
		{
			delete student[num];
			student.erase(student.begin() + num);
			isThere = true;
			break;
		}
	}

	if (!isThere)
	{
		std::cout << "[ERROR] �߸��� �Է�";
	}
	else
	{
		system("cls");
		printAll(student);
	}
}

void bubbleSort(std::vector<Student*>& student, bool bName, bool bAge, bool bForward)
{
	for (int i = 0; i < student.size() - 1; i++)
	{
		for (int j = 0; j < student.size() - i - 1; j++)
		{
			//std::cout << "i = " << i << ", j = " << j << std::endl;
			// �̸����� ����
			if (bName)
			{
				if (student[j]->getName() > student[j + 1]->getName() && bForward)
					std::swap(student[j], student[j + 1]);
				else if (student[j]->getName() < student[j + 1]->getName() && !bForward)
					std::swap(student[j], student[j + 1]);
			}

			// ���̷� ����
			if (bAge)
			{
				if (student[j]->getAge() > student[j + 1]->getAge() && bForward)
					std::swap(student[j], student[j + 1]);
				else if (student[j]->getAge() < student[j + 1]->getAge() && !bForward)
					std::swap(student[j], student[j + 1]);
			}
		}
	}

	system("pause");
	system("cls");
	printAll(student);
}