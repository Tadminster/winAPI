#include "framework.h"
#include "obj_player.h"

obj_player::obj_player() : obj_prototype(), hand(1), charge_current(0.f), charge_max(100.f)
{
    // 플레이어 외형
    for (int i = 0; i < 360; i++)
    {
        //            중점         멀어진 길이
        vertex[i].x = cosf(i*ToRadian);
        vertex[i].y = sinf(i*ToRadian);
    }

    hasGauge_Charging = true;
    hasGauge_Hp = true;
    this->gauge_charging = new obj_chargingBar(this);
    this->gauge_hp = new obj_chargingBar(this);
}

void obj_player::Update()
{
    obj_prototype::Update();

    // 차징바 정보 갱신
    this->gauge_charging->Update
    (
        this->charge_current,
        this->charge_max,
        Vector2(this->get_worldPos().x - 20.f, this->get_worldPos().y + 50.f)
    );
    
    this->gauge_hp->Update
   (
       this->Hp_current,
       this->Hp_max,
       Vector2(this->get_worldPos().x - 20.f, this->get_worldPos().y - 10.f)
   );
}

void obj_player::Render()
{
    obj_prototype::Render();

    // 버텍스 설정
    Vector2 TransformVertex[360];
    for (int i = 0; i < 360; i++)
    {

        //                      vector * M
        TransformVertex[i] = Vector2::Transform(vertex[i], W);

    }

    //  그리기
    MoveToEx(g_hdc, TransformVertex[0].x, TransformVertex[0].y, nullptr);
    for (int i = 1; i < 360; i++)
        LineTo(g_hdc, TransformVertex[i].x, TransformVertex[i].y);
    LineTo(g_hdc, TransformVertex[0].x, TransformVertex[0].y);

    // 게이지 랜더
    this->gauge_hp->Render();
    if (this->charge_current > 0.f)
        this->gauge_charging->Render();
}

// 현재 무기 가져오기
int obj_player::get_hand()
{
    return this->hand;
}

// 무기 변경
void obj_player::set_hand(int type_Branch)
{
    if (type_Branch == 1)
    {
        this->hand = 1;
    }
    else if (type_Branch == 2)
    {
        this->hand = 2;
    }
    else if (type_Branch == 3)
    {
        this->hand = 3;
    }
    else if (type_Branch == 0)
    {
        this->hand = 0;
    }
}

Vector2 obj_player::get_playerPos()
{
    return this->pos;
}