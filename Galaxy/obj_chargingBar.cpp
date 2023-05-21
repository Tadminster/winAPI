#include "framework.h"
#include "obj_chargingBar.h"

obj_chargingBar::obj_chargingBar(class obj_prototype* player)
{
    this->textout = new sys_textOut();
    
    this->scale.x = 1.f ;
    this->scale.y = 10.f;
    this->rotation.z = atan2f(player->get_right().y, player->get_right().x);
    
    this->pos.x = 1.f;
    this->pos.y = 1.f;

    this->pivot = OFFSET_L;
    this->hasAxis = false;
}

obj_chargingBar::~obj_chargingBar()
{
    delete this->textout;
}

void obj_chargingBar::Update(float value_cur, float value_max, Vector2 worldPos)
{
    
    this->scale.x = min(value_cur, value_max);
   
    this->pos.x = worldPos.x - 20.f;
    this->pos.y = worldPos.y - 30.f;
    
    obj_rect::Update();
    std::string str =  std::to_string(value_cur);
    this->textout->Update(this->pos, str);

    // S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
    // R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
    // R2 = Matrix::CreateFromYawPitchRoll(rotation2.y, rotation2.x, rotation2.z);
    // T = Matrix::CreateTranslation(pos.x, pos.y, 0.0f);
    //
    // RT = R * T * R2;
    //
    //
    // //포인터에 주소값이 있다면
    // if (P)
    // {
    //     RT *= *P;
    // }
    // W = S * RT;
}


void obj_chargingBar::Render()
{
    obj_rect::Render();
    textout->Render();

}