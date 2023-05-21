
#include "framework.h"
#include "obj_weapon_shotgun.h"

obj_weapon_shotgun::obj_weapon_shotgun()
{
    //local space
    vertex[0].x = 0;
    vertex[0].y = 0;

    vertex[1].x = 1;
    vertex[1].y = 0;

    this->name = "샷건";
    this->Ammo_Max = 300;
    this->Ammo_Current = 300;
    this->Damage = 6;
    this->Ammo_Speed = 400.f;
    this->fireRate = 1.5;
    this->range = 550.f;
}

void obj_weapon_shotgun::Render()
{
    obj_weapon_prototype::Render();
}

void obj_weapon_shotgun::Fire(class obj_player* shooter)
{
    float currentTime = sys_timer::GetInstance()->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (this->Ammo_Current > 0 && elapsedTime >= timeSinceLastShot)
    {
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{atan2f(player->get_right().y, player->get_right().x)};
        // 총구 위치 계산
        Vector2 muzzle = Vector2(this->GetWorldPos() + shooter->get_right() * scale.x);

        for (int i = 0; i < 7; i++)
        {
            float random_x{ RANDOM->Float(0.9f, 1.1f) };
            float random_y{ RANDOM->Float(0.9f, 1.1f) };
            float shot_angle;

            // if (i%2 == 0)
            //     shot_angle = rotation_z + i / 0.5f * ToRadian;
            // else
            //     shot_angle = rotation_z + -i / 0.5f * ToRadian;
            // 탄생성
            const obj_weapon_bullet bullet
            (
                muzzle,
                Vector2(shooter->get_right().x * random_x,shooter->get_right().y * random_y),
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
}
