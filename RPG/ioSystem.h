#pragma once
#include "framework.h"
#include <conio.h>

class ioSystem
{
public:
	/* 사용자 입력 받기 */
	int		input_number(int min, int max);
	/* 입력으로 UP, DOWN 방향키만 받음 */
	int		input_arrow_col(std::string* texts, int arraySize);

	/*
	* 플레이어 이동을 위한 방향키 입력
	* return 1 : UP
	* return 2 : DOWN
	* return 3 : LEFT
	* return 4 : RIGHT
	*/
	int		input_arrow_all();

	void	output_text(std::string* texts, int arraySize, int current);
	void	output_img_main();
};