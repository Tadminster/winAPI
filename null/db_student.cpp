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
		if (this->sex % 2 == 1) std::cout << "남자";
		else if (this->sex % 2 == 0) std::cout << "여자";
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
	// 정렬 오름차순, 내림차순
	bool bForward = true;
	bool bSortArrow = false;

	// Student 벡터 선언
	std::vector<Student*> student;

	// 학생 기록부 시작
	while (1)
	{
		std::cout << "학생 기록부" << std::endl;
		std::cout << "[1] 학생 추가하기" << std::endl;
		std::cout << "[2] 학생 삭제하기" << std::endl;
		std::cout << "[3] 학생 정렬하기" << std::endl;

		std::cout << "원하는 옵션을 선택하세요: ";
		std::string input;

		// 정렬방향 변경시 바로 넘어가기
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
			std::cout << "[1] 이름으로 찾기" << std::endl;
			std::cout << "[2] 나이로 찾기" << std::endl;
			std::cout << "원하는 옵션을 선택하세요: ";
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
				std::cout << "[0] 정렬방향 변경: 현재 오름차순" << std::endl;
			else 
				std::cout << "[0] 정렬방향 변경: 현재 내림차순" << std::endl;
			std::cout << "[1] 이름 순으로 정렬" << std::endl;
			std::cout << "[2] 나이 순으로 정렬" << std::endl;
			std::cout << "원하는 옵션을 선택하세요: ";
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
			std::cout << "[!] 잘못된 입력" << std::endl << std::endl;
			system("pause");
			system("cls");
		}
	}

	deleteAll(student);
}

void addStudent(std::vector<Student*>& student)
{
	std::cout << std::endl;
	std::cout << "이름을 입력하세요: ";
	std::string name;
	std::cin >> name;

	std::string textAge = "나이를 입력하세요: ";
	int age{ intInput(0, 99, textAge) };

	std::cout << "짝수는 남성, 홀수는 여성" << std::endl;
	std::string textSex = "성별을 입력하세요: ";
	int sex{ intInput(0, 99, textSex) };

	Student* newStudent = new Student(name, age, sex, student.size());
	/*newStudent->setName(name);
	newStudent->setAge(age);
	newStudent->setSex(sex);*/

	student.push_back(newStudent);
}

/* 플레이어 입력 */
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
			std::cout << "[!] '문자'가 입력되었습니다." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < min || input > max)
			std::cout << "[!] '값'이 작거나 큽니다." << std::endl;
		else break;
		std::cout << std::endl;
	}

	return input;
}


void printAll(std::vector<Student*> student)
{
	std::cout << "\t이름\t나이\t성별" << std::endl;
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
	//type == 0 이름으로 검색, type == 1 나이로 검색
	if (type == 0)
		std::cout << "찾을 이름 검색: ";
	else if (type == 1)
		std::cout << "찾을 나이 검색: ";

	// 문자열 입력받고
	std::string tempStr;
	std::cin >> tempStr;

	// 정규식 패턴에 추가하고
	std::regex pattern(tempStr);


	system("cls");
	std::cout << "\t이름\t나이\t성별" << std::endl;
	for (int i = 0; i < student.size(); i++)
	{

		// 대상 텍스트 지정
		std::string targetStr;
		if (type == 0)
			targetStr = student[i]->getName();
		else if (type == 1)
			targetStr = std::to_string(student[i]->getAge());

		// 패턴찾으면 출력 & tempNum에 push_back
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
	std::string textDelete = "삭제할 번호 입력: ";
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
		std::cout << "[ERROR] 잘못된 입력";
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
			// 이름으로 정렬
			if (bName)
			{
				if (student[j]->getName() > student[j + 1]->getName() && bForward)
					std::swap(student[j], student[j + 1]);
				else if (student[j]->getName() < student[j + 1]->getName() && !bForward)
					std::swap(student[j], student[j + 1]);
			}

			// 나이로 정렬
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