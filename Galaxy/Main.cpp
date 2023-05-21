#include "framework.h"
#include "Main.h"

Main::Main()
{
    // 게임 관련
    time_remaining = new sys_textOut();

    // 플레이어
    for (int i=0; i<numOfPlayer; i++)
        player[i] = new obj_player();
    
    // 테스트용
    this->w_prototype = new obj_weapon_prototype();
    this->w_prototype->SetParentRT(*player[0]);

    for (int i=0; i<numOfPlayer; i++)
    {
        this->pistol[i] = new obj_weapon_pistol();
        this->pistol[i]->SetParentRT(*player[i]);

        this->shotgun[i] = new obj_weapon_shotgun();
        this->shotgun[i]->SetParentRT(*player[i]);

        this->sniper[i] = new obj_weapon_sniper();
        this->sniper[i]->SetParentRT(*player[i]);
    }



    // this->star = new obj_star();
    // this->star->set_parentT(*player);
}

Main::~Main()
{
    for (int i=0; i<numOfPlayer; i++)
    {
        delete this->pistol[i];
        delete this->shotgun[i];
        delete this->sniper[i];
        delete this->player[i];
    }
}

void Main::Init()
{
    HDC	hdc = GetDC(g_hwnd); //기존핸들

    g_hdc = CreateCompatibleDC(hdc);	//
    HBITMAP m_hBitmap = CreateCompatibleBitmap(hdc, 800, 800);//만들크기
    HBITMAP m_hOldBitmap = static_cast<HBITMAP>(SelectObject(g_hdc, m_hBitmap));
    ReleaseDC(g_hwnd, hdc);

    this->w_prototype->scale.x = 20.f;
    this->w_prototype->scale.y = 3.f;
    this->w_prototype->pos.x = 5.f;
    this->w_prototype->pos.y = 14.f;

    
    for (int i=0; i<numOfPlayer; i++)
    {
        this->player[i]->scale.x = 15.0f;
        this->player[i]->scale.y = 15.0f;
        this->player[i]->Hp_current = 100;
        this->player[i]->Hp_max = 100;
        this->player[i]->move_speed = 250;

        this->pistol[i]->scale.x = 10.f;
        this->pistol[i]->scale.y = 2.f;
        this->pistol[i]->pos.x = 5.f;
        this->pistol[i]->pos.y = 14.f;

        this->shotgun[i]->scale.x = 15.f;
        this->shotgun[i]->scale.y = 3.f;
        this->shotgun[i]->pos.x = 5.f; 
        this->shotgun[i]->pos.y = 13.f; 

        this->sniper[i]->scale.x = 30.f;
        this->sniper[i]->scale.y = 2.f;
        this->sniper[i]->pos.x = 5.f;
        this->sniper[i]->pos.y = 14.f;

        // this->star[i]->scale.x = 10.f;
        // this->star[i]->scale.y = 10.f;
        // this->star[i]->set_localPos_x(50.f);
    }
    this->player[0]->pos.x = 200.0f;
    this->player[0]->pos.y = 600.0f;
    this->player[1]->pos.x = 600.0f;
    this->player[1]->pos.y = 600.0f;

    turn = 0;
    turnTime = 0.f;
}

void Main::Release()
{
}

void Main::Update()
{
    if (TIMER->GetTick(turnTime, 10.f))
    {
        if (turn == 0) turn = 1;
        else if (turn == 1) turn = 0;
        turnTime = 0.f;
    }
    
    // 마우스 방향으로 바라보게
    Vector2 mouse_point (INPUT->mouseScreenPos - this->player[turn]->get_worldPos());
    player[turn]->rotation.z =   atan2f (mouse_point.y, mouse_point.x);
    
    
    if (sys_input::GetInstance()->KeyDown('1'))
    {
        this->player[turn]->set_hand(1);
    }
    else if (sys_input::GetInstance()->KeyDown('2'))
    {
        this->player[turn]->set_hand(2);
    }
    else if (sys_input::GetInstance()->KeyDown('3'))
    {
        this->player[turn]->set_hand(3);
    }
    else if (sys_input::GetInstance()->KeyDown('0'))
    {
        this->player[turn]->set_hand(0);
    }
    
    // 차지
    if (sys_input::GetInstance()->KeyPress(VK_LBUTTON))
    {
        if (this->player[turn]->charge_current >= this->player[turn]->charge_max)
            this->player[turn]->charge_current = this->player[turn]->charge_max;
        else
            this->player[turn]->charge_current += 100.f * DELTA;
    }

    // 격발
    if (sys_input::GetInstance()->KeyUp(VK_LBUTTON))
    {
        if (this->player[turn]->get_hand() == 1)
            this->pistol[turn]->Fire(player[turn]);
        
        else if (this->player[turn]->get_hand() == 2)
            this->shotgun[turn]->Fire(player[turn]);
        
        else if (this->player[turn]->get_hand() == 3)
            this->sniper[turn]->Fire(player[turn]);
        
        else if (this->player[turn]->get_hand() == 0)
            this->w_prototype->Fire(player[0]);

        // 격발시 차지 초기화
        this->player[turn]->charge_current = 0.f;
        // 턴 넘기기
        if (turn == 0) turn = 1;
        else if (turn == 1) turn = 0;
        turnTime = 0.f;
    }


    if (sys_input::GetInstance()->KeyPress('W')) // 상
    {
        player[turn]->move_worldPos(UP * DELTA * 200);

        if (player[turn]->pos.y < 0 + player[turn]->scale.y) player[turn]->set_worldPos_y(20);
    }
    if (sys_input::GetInstance()->KeyPress('S')) // 하
    {
        player[turn]->move_worldPos(DOWN * DELTA * 200);

        if (player[turn]->pos.y > 800 - player[turn]->scale.y) player[turn]->set_worldPos_y(780);
    }
    if (sys_input::GetInstance()->KeyPress('A')) // 좌
    {
        player[turn]->move_worldPos(LEFT * DELTA * 200);

        if (player[turn]->pos.x < 0 + player[turn]->scale.x) player[turn]->set_worldPos_x(20);
    }
    if (sys_input::GetInstance()->KeyPress('D')) // 우
    {
        player[turn]->move_worldPos(RIGHT * DELTA * 200);

        if (player[turn]->pos.x > 800 - player[turn]->scale.x) player[turn]->set_worldPos_x(780);
    }

    GetLocalTime(&system_time);
}

void Main::LateUpdate()
{
    w_prototype->Update();
    w_prototype->Update_Bullets();

    std::string time_temp = "현재 " + std::to_string(turn + 1) + "P의 턴, 남은 시간: " + std::to_string(10.f-turnTime);
    time_remaining->Update(Vector2(250, 150), time_temp);
    
    for (int i=0; i<numOfPlayer; i++)
    {
        this->player[i]->Update();
        this->pistol[i]->Update();
        this->pistol[i]->Update_Bullets();
        this->shotgun[i]->Update();
        this->shotgun[i]->Update_Bullets();
        this->sniper[i]->Update();
        this->sniper[i]->Update_Bullets();
    
        // this->star[i]->Update();
        // this->star[i]->rotation2.z += 1 * ToRadian;

    }

    // 충돌 처리
    this->pistol[0]->collision_Bullets(player[1]);
    this->shotgun[0]->collision_Bullets(player[1]);
    this->sniper[0]->collision_Bullets(player[1]);
    this->pistol[1]->collision_Bullets(player[0]);
    this->shotgun[1]->collision_Bullets(player[0]);
    this->sniper[1]->collision_Bullets(player[0]);
}

void Main::Render()
{

    PAINTSTRUCT ps;
    //hdc-> 도화지
    g_frontHdc = BeginPaint(g_hwnd, &ps);
    PatBlt(g_hdc, 0, 0, 800, 800, WHITENESS);

    time_remaining->Render();


    std::string str = "FPS:" + std::to_string(TIMER->GetFramePerSecond()) +
    "\n WorldTime:" + std::to_string(TIMER->GetWorldTime()) +
    "\n Delta:" + std::to_string(DELTA);
    TextOutA(g_hdc, 10, 10, str.c_str(), str.size());

    std::string str2 =
        "X: " + std::to_string(static_cast<int>(INPUT->mouseScreenPos.x)) + ", "
        "Y: " + std::to_string(static_cast<int>(INPUT->mouseScreenPos.y));
    TextOutA(g_hdc, 10, 30, str2.c_str(), str2.size());

    {   // 텍스트 출력
        std::string str[3] =
        {
            "[W][A][S][D] 이동",
            "[좌클릭] 격발",
            "[1]권총, [2]샷건, [3]저격총"
        };

        int tempInt{ 0 };
        for (auto& i : str)
            TextOutA(g_hdc, 540, 10 + 20 * tempInt++, i.c_str(), i.size());
    }

    HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(100, 220, 100));
    SelectObject(g_hdc, hPen1);

    // 플레이어 렌더링
    for (int i=0; i<numOfPlayer; i++)
        this->player[i]->Render();
    
    // this->star->Render();

    DeleteObject(hPen1);

    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    SelectObject(g_hdc, hPen2);
    
    
    for (int i=0; i<numOfPlayer; i++)
    {
        // 들고 있는 무기 렌더링
        if (this->player[i]->get_hand() == 1)
        {
            this->pistol[i]->Render();
            if (turn == i) this->pistol[i]->printStatus();
        }
        else if (this->player[turn]->get_hand() == 2)
        {
            this->shotgun[i]->Render();
            if (turn == i) this->shotgun[i]->printStatus();
        }
        else if (this->player[turn]->get_hand() == 3)
        {
            this->sniper[i]->Render();
            if (turn == i) this->sniper[i]->printStatus();
        }
        else if (this->player[turn]->get_hand() == 0)
        {
            this->w_prototype->Render();
            if (turn == i) this->w_prototype->printStatus();
        }

        // 발사된 탄 렌더링
        this->pistol[i]->Render_Bullets();
        this->shotgun[i]->Render_Bullets();
        this->sniper[i]->Render_Bullets();
        this->w_prototype->Render_Bullets();
    }

    DeleteObject(hPen2);

    HPEN hPen3 = CreatePen(PS_SOLID, 1, RGB(255, 100, 100));
    SelectObject(g_hdc, hPen3);

    //원래는 컴퓨터
    DeleteObject(hPen3);


    BitBlt( g_frontHdc, 0, 0, 800, 800,
            g_hdc, 0, 0, SRCCOPY);
    
    EndPaint(g_hwnd, &ps);
}

void Main::ResizeScreen()
{
}
