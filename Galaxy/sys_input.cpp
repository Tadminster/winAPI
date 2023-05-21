﻿#include "framework.h"

sys_input::sys_input()
{
    //시작주소로부터 어디까지 전부 0으로 초기화
    ZeroMemory(keyState, sizeof(keyState));
    ZeroMemory(keyOldState, sizeof(keyOldState));
    ZeroMemory(keyMap, sizeof(keyMap));
}

sys_input::~sys_input()
{
}

bool sys_input::KeyDown(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_DOWN;
}

bool sys_input::KeyPress(int KeyCode)
{
    return keyMap[KeyCode] <= KEY_INPUT_STATUS_PRESS;
}

bool sys_input::KeyUp(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_UP;
}

void sys_input::Update()
{
    //Screen To World
   //mouseWorldPos.x = mouseScreenPos.x - app.GetHalfWidth() + CAM->position.x;
   ////mouseWorldPos.y = app.GetHeight() - app.GetHalfHeight() - mouseScreenPos.y ;
   //mouseWorldPos.y = app.GetHalfHeight() - mouseScreenPos.y + CAM->position.y;

    //메모리복사 keyOldState = keyState 
    memcpy(keyOldState, keyState, sizeof(keyOldState));

    //기존의 배열값 초기화
    ZeroMemory(keyState, sizeof(keyState));

    ZeroMemory(keyMap, sizeof(keyMap));

    //BOOL a;
    //현재 호출상태에서의 키입력값을 가져오는 함수
    if (GetKeyboardState(keyState))
    {
        for (UINT i = 0; i < 256; i++)
        {
            byte key = keyState[i] & 0x80;
            //삼항연산자   (bool)? 1{} 0{}
            //키를 누른상태면 1, 아니면 0으로 대입
            keyState[i] = key ? 1 : 0;

            int oldState = keyOldState[i];
            int state = keyState[i];

            if (oldState == 0 && state == 1)
                keyMap[i] = KEY_INPUT_STATUS_DOWN; //이전 0, 현재 1 - KeyDown
            else if (oldState == 1 && state == 0)
                keyMap[i] = KEY_INPUT_STATUS_UP; //이전 1, 현재 0 - KeyUp
            else if (oldState == 1 && state == 1)
                keyMap[i] = KEY_INPUT_STATUS_PRESS; //이전 1, 현재 1 - KeyPress
            else
                keyMap[i] = KEY_INPUT_STATUS_NONE;
        }
    }
    // 0x80    1000  0000  이전에안눌렀고 지금 누름
    // 0x81    1000  0001  이전에도눌럿고 지금 누름
    // 0x00    0000  0000
    // 0x01    0000  0001

    //&

    // 0x80    1000  0000
}
