#include "framework.h"
#include "obj_weapon_pistol.h"

obj_weapon_pistol::obj_weapon_pistol()
{
    this->name = "권총";
    this->Ammo_Max = 9999;
    this->Ammo_Current = 9999;
    this->Damage = 15;
    this->Ammo_Speed = 400.f;
    this->fireRate = 4;
    this->range = 800.f;
}

void obj_weapon_pistol::Render()
{
    obj_weapon_prototype::Render();
}

void obj_weapon_pistol::Fire(class obj_player* shooter)
{
    float currentTime = sys_timer::GetInstance()->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (this->Ammo_Current > 0 && elapsedTime >= timeSinceLastShot)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(this->GetWorldPos() + shooter->get_right() * scale.x);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{ atan2f(shooter->get_right().y, shooter->get_right().x) };

        // 탄생성
        const obj_weapon_bullet bullet
        (
            muzzle,
            shooter->get_right(),
            this->Ammo_Speed * DELTA,
            this->range,
            shooter->charge_current * 5.f
        );
        //벡터에 탄 push
        bullets.push_back(bullet);
        //탄 수량 감소
        this->Ammo_Current = max(this->Ammo_Current - 1, 0);    

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastShot = 1.0f / this->fireRate;
    }
}

void obj_weapon_pistol::Render_Bullets()
{
    for (auto& ammo : this->bullets)
    {
        ammo.Render();
    }
}
