#include "framework.h"
#include "obj_weapon_bullet.h"

// obj_weapon_bullet::obj_weapon_bullet(Vector2 pos, float speed, float range, float rotation_z, float charging_scale)
obj_weapon_bullet::obj_weapon_bullet(Vector2 pos, Vector2 direction, float speed, float range, float charge)
    : speed(speed), range(range), traveledDistance(0.f), Damage(5), Pos_Initial(pos), Hp(1), pressPower(charge)
{
    // 탄의 생성위치
    this->pos.x = pos.x;
    this->pos.y = pos.y;

    // 탄의 크기
    this->scale.x = 5.f;
    this->scale.y = 5.f;
    
    // 탄의 각도
    // this->rotation.z = rotation_z;
    this->shooting_Dir = direction;

    // 중력
    this->gravityDir = DOWN;
    this->gravityForce = 0.0f;
    
    this->pivot = OFFSET_L;
    this->hasAxis = false;
    this->hasGauge_Charging = false;
    this->hasGauge_Hp = false;
}

void obj_weapon_bullet::Update()
{
    this->scale.x = 5.f;
    this->scale.y = 3.f;

    obj_prototype::Update();

    // 탄이 이동한 거리 계산
    this->Pos_Current.x += speed;
    this->Pos_Current.y += speed;
    traveledDistance += std::sqrt(std::pow(speed, 2) + std::pow(speed, 2));
}

void obj_weapon_bullet::Render()
{
    obj_rect::Render();
}

bool obj_weapon_bullet::hasIntersect(obj_prototype* target) const
{
    Vector2 temp_vector(target->get_worldPos().x - this->pos.x, target->get_worldPos().y - this->pos.y);
    float distance = sqrt(pow((temp_vector.x), 2) + pow((temp_vector.y), 2));
    float radius_sum = target->scale.x + this->scale.x;
    float radius_diff = abs( target->scale.x - this->scale.x);
    if (distance <= radius_sum) 
    {
        return true;
    }
    return false;
}

void obj_weapon_bullet::reflection_y()
{
    shooting_Dir.x = -shooting_Dir.x; 

    /*Vector2 dir =
        Vector2(cosf(rotation.z), sinf(rotation.z));
    rotation.z = atan2f(dir.y, -dir.x);*/

    pressPower *= 0.7f;
    gravityForce *= 0.7f;
}

void obj_weapon_bullet::reflection_x()
{
    shooting_Dir.y = -shooting_Dir.y; 
    gravityForce = -gravityForce;

    //Vector2 dir =
    //	Vector2(cosf(rotation.z), sinf(rotation.z));
    //rotation.z = atan2f(-dir.y, dir.x);

    pressPower *= 0.7f;
    gravityForce *= 0.7f;
}
