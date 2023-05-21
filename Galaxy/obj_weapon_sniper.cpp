#include "framework.h"
#include "obj_weapon_sniper.h"

obj_weapon_sniper::obj_weapon_sniper()
{
    //local space
    vertex[0].x = 0;
    vertex[0].y = 0;

    vertex[1].x = 1;
    vertex[1].y = 0;

    this->name = "저격총";
    this->Ammo_Max = 200;
    this->Ammo_Current = 200;
    this->Ammo_Speed = 900.f;
    this->Damage = 35;
    this->fireRate = 1;
    this->range = 1400.f;
}

void obj_weapon_sniper::Render()
{
    obj_weapon_prototype::Render();
}

void obj_weapon_sniper::Fire(class obj_player* shooter)
{
    float currentTime = sys_timer::GetInstance()->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (this->Ammo_Current > 0 && elapsedTime >= timeSinceLastShot)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(this->GetWorldPos() + shooter->get_right() * scale.x);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{atan2f(player->get_right().y, player->get_right().x)};
        
        // if (charge < 1.f)
        {
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
        }
        // else
        // {
        //     // 탄생성
        //     const Object_Weapon_Laser bullet
        //     (
        //         this->GetWorldPos(),
        //         this->Ammo_Speed + (charge * 6),
        //         this->range + charge * 10,
        //         z,
        //         0
        //     );
        //     //벡터에 탄 push
        //     bullets.push_back(bullet);
        // }
        
        //탄 수량 감소
        this->Ammo_Current = max(this->Ammo_Current - 1, 0);    

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastShot = 1.0f / this->fireRate;
    }
}
