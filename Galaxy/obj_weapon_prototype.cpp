#include "framework.h"
#include "obj_weapon_prototype.h"

obj_weapon_prototype::obj_weapon_prototype() : P(nullptr)
{
    vertex[0].x = 0 - 0.5f;
    vertex[0].y = 0 - 0.5f;

    vertex[1].x = 1 - 0.5f;
    vertex[1].y = 0 - 0.5f;

    vertex[2].x = 1 - 0.5f;
    vertex[2].y = 1 - 0.5f;

    vertex[3].x = 0 - 0.5f;
    vertex[3].y = 1 - 0.5f;

    this->name = "PROTOTYPE";
    this->Ammo_Max = 500;
    this->Ammo_Current = 500;
    this->Ammo_Speed = 400.f;
    this->fireRate = 10;
    this->range = 700.f;
}

obj_weapon_prototype::~obj_weapon_prototype() {}

void obj_weapon_prototype::Update()
{
    /*S._11 = scale.x;
    S._22 = scale.y;

    R._11 = cos(rotation * ToRadian);
    R._12 = -sin(rotation * ToRadian);
    R._21 = sin(rotation * ToRadian);
    R._22 = cos(rotation * ToRadian);

    T._41 = pos.x;
    T._42 = pos.y;
    T._43 = 0;*/

    Pi = Matrix::CreateTranslation(pivot.x, pivot.y, 0.0f);
    S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
    R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
    R2 = Matrix::CreateFromYawPitchRoll(rotation2.y, rotation2.x, rotation2.z);
    T = Matrix::CreateTranslation(pos.x, pos.y, 0.0f);

    RT = R * T * R2;
	

    //포인터에 주소값이 있다면
    if (P)
    {
        RT *= *P;
    }
    W = Pi * S * RT;
}

void obj_weapon_prototype::Render()
{
    Vector2 TransformVertex[4];
    for (int i = 0; i < 4; i++)
    {
        //                      vector * M
        TransformVertex[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_hdc, TransformVertex[0].x, TransformVertex[0].y, NULL);
    LineTo(g_hdc, TransformVertex[1].x, TransformVertex[1].y);
    LineTo(g_hdc, TransformVertex[2].x, TransformVertex[2].y);
    LineTo(g_hdc, TransformVertex[3].x, TransformVertex[3].y);
    LineTo(g_hdc, TransformVertex[0].x, TransformVertex[0].y);
}

void obj_weapon_prototype::MoveWorldPos(Vector2 Velocity)
{
    if (!P)
    {
        pos += Velocity;
    }
    else
    {
        Vector2 locVelocity = Vector2::TransformNormal(Velocity, (*P).Invert());
        pos += locVelocity;
    }
}

void obj_weapon_prototype::SetWorldPos(Vector2 worldPos)
{
    if (not P)
    {
        pos = worldPos;
    }
    else
    {
        Vector2 location = Vector2::Transform(worldPos, (*P).Invert());
        pos = location;
    }
}

void obj_weapon_prototype::SetWorldPosX(float worldPosX)
{
    if (!P)
    {
        pos.x = worldPosX;
    }
    else
    {
        Vector2 location = Vector2::Transform(Vector2(worldPosX, 0), (*P).Invert());
        pos.x = location.x;
    }
}

void obj_weapon_prototype::SetWorldPosY(float worldPosY)
{
    if (!P)
    {
        pos.y = worldPosY;
    }
    else
    {
        Vector2 location = Vector2::Transform(Vector2(0, worldPosY), (*P).Invert());
        pos.y = location.y;
    }
}

void obj_weapon_prototype::Fire(class obj_player* shooter)
{
    float currentTime = sys_timer::GetInstance()->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (this->Ammo_Current > 0 && elapsedTime >= timeSinceLastShot) 
    {
        // 총구 위치 계산
        Vector2 muzzle(this->GetWorldPos().x, this->GetWorldPos().y);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{atan2f(player->get_right().y, player->get_right().x)};
        
        const obj_weapon_bullet bullet
        (
            muzzle,                         // 탄의 발사위치(worldPos)
            shooter->get_right(),           // 각도
            this->Ammo_Speed * DELTA,       // 탄속
            this->range,                    // 사거리
            shooter->charge_current * 5.f   // 탄
        );
        this->bullets.push_back(bullet);
        this->Ammo_Current = max(this->Ammo_Current - 1, 0);

        this->lastShotTime = currentTime;
        this->timeSinceLastShot = 1.0f / this->fireRate;
    }
}

void obj_weapon_prototype::Update_Bullets()
{
    int temp{ 0 };
    for (auto& ammo : this->bullets)
    {
        // 탄의 위치 이동
        // ammo.pos += Vector2(cosf(ammo.rotation.z), sinf(ammo.rotation.z)) * (ammo.speed);
        // ammo.pos += Vector2(0, ammo.gravity_sin);
        // ammo.gravity_sin += ammo.gravity_cos * DELTA;

        ammo.gravityForce += 500.0f * DELTA;

        Vector2 velocity = (ammo.shooting_Dir * ammo.pressPower
            + ammo.gravityDir * ammo.gravityForce);
        ammo.move_worldPos(velocity * DELTA);
        
        // 탄이 맵 밖을 벗어났으면
        int map_side{ 10 };
        // x축
        if (ammo.get_localPos().x < 0 + map_side)
        {
            ammo.set_worldPos_x(0 + map_side);
            ammo.reflection_y();
            // ammo.rotation.z = atan2f(ammo.get_right().y, -ammo.get_right().x);
        }
        else if (ammo.get_localPos().x > 800 - map_side)
        {
            ammo.set_worldPos_x(800 - map_side);
            ammo.reflection_y();
            // ammo.rotation.z = atan2f(ammo.get_right().y, -ammo.get_right().x);
        }
        // y축
        if (ammo.get_localPos().y < 0 + map_side)
        {
            ammo.set_worldPos_y(0 + map_side);
            ammo.reflection_x();
            // ammo.rotation.z = atan2f(-ammo.get_right().y, ammo.get_right().x);
        }
        else if (ammo.get_localPos().y > 800 - map_side)
        {
            ammo.set_worldPos_y(800 - map_side - 5);
            ammo.reflection_x();
            // ammo.rotation.z = atan2f(-ammo.get_right().y, ammo.get_right().x);
        }

        // 탄의 정보 업데이트
        ammo.Update();

        // 탄의 체력이 0이면 삭제
        // if (ammo.Hp == 0) ammo.traveledDistance = range;
    }


    // 탄이 사거리를 벗어났으면
    bullets.erase(
        std::remove_if
        (
            bullets.begin(),
            bullets.end(),
            [](const obj_weapon_bullet& b
                ) { return b.hasTraveledTooFar(); }),
        bullets.end()
    );
}


bool obj_weapon_prototype::collision_Bullets(class obj_player* target)
{
    // 탄이 대상과 충돌했으면 삭제
    int tempCnt{ 0 };
    for (auto& ammo : bullets)
    {
        if (ammo.hasIntersect(target))
        {
            bullets.erase(bullets.begin() + tempCnt);
            target->Hp_current = max(0, target->Hp_current - this->Damage);
            return true;
        }
        tempCnt++;
    }

    return false;
    
    //auto hasIntersect = [target](const obj_weapon_bullet& b) { return b.hasIntersect(target); };
    //bullets.erase(
    //    std::remove_if
    //    (
    //        bullets.begin(),
    //        bullets.end(),
    //        hasIntersect
    //    ),
    //    bullets.end()
    //);
}

// bool obj_weapon_prototype::collision_Bullets(std::vector<obj_weapon_bullet>& target_bullet, int damage)
// {
//     //obj_weapon_prototype::Update_Bullets();
//     // 탄이 대상과 충돌했으면 삭제
//     int tempCnt{ 0 };
//     for (auto& ammo : bullets)
//     {
//         tempCnt = 0;
//         for (auto& target : target_bullet)
//         {
//             if (ammo.hasIntersect(&target))
//             {
//                 target_bullet.erase(target_bullet.begin() + tempCnt);
//                 ammo.Hp = max(0, ammo.Hp - this->Damage);
//                 return true;
//             }
//             tempCnt++;
//         }
//     }
//
//     return false;
// }

void obj_weapon_prototype::Render_Bullets()
{
    for (auto& ammo : this->bullets)
    {
        ammo.Render();
    }
}

void obj_weapon_prototype::printStatus()
{
    
    std::string str[] =
    {
        "[총기] " + this->name,
        "[탄약] " + (this->Ammo_Current>999?"무한":std::to_string(this->Ammo_Current)),
        "[발당 피해] " + std::to_string(this->Damage),
        // "[발사 속도] 초당 " + std::to_string(this->fireRate),
        // "[포구 속도] 초당 " + std::to_string(static_cast<int>(this->Ammo_Speed)),
        "[유효 거리] " + std::to_string(static_cast<int>(this->range))
    };

    int tempInt{ 0 };
    for (int i=0; i<str->size(); i++)
    {
        TextOutA(g_hdc, 20, 660 + 20 * tempInt++, str[i].c_str(), str[i].size());
    }


    //std::string gun_text1 = "[탄약] " + std::to_string(this->Ammo_Current);
    //TextOutA(g_hdc, 10, 300, gun_text1.c_str(), gun_text1.size());
}
