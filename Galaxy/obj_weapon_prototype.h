#pragma once

class obj_weapon_prototype
{
protected:
    Matrix Pi, S, R, R2, T, RT, W;
    Matrix* P;

    Vector2     vertex[4];                      // 총의 모양
    std::string name;       
    int         Ammo_Current;                   // 잔탄
    int         Ammo_Max;                       // 최대잔탄
    int         Damage;     
    float       Ammo_Speed;                     // 탄속
    float       fireRate;                       // 공속
    float       range;                          // 사정거리
    float       lastShotTime;                   // 마지막 발사 시간
    float       timeSinceLastShot;              // 마지막 발사 이후 시간
    std::vector<obj_weapon_bullet> bullets;     // 발사된 총알

public:
    Vector2 pivot;
    Vector2	scale;
    Vector2	pos;
    Vector3	rotation;	// 자전
    Vector3	rotation2;	// 공전
    
public:
    obj_weapon_prototype();
    virtual ~obj_weapon_prototype();
    virtual void Update();
    virtual void Render();
    
    void SetParentRT(obj_weapon_prototype& src) { P = &src.RT; }
    void SetParentRT(obj_prototype& src) { P = &src.get_RT(); }

    Vector2 GetRight() { return Vector2(RT._11, RT._12); }
    Vector2 GetUp() { return Vector2(RT._21, RT._22); }
    Vector2 GetWorldPos() { return Vector2(RT._41, RT._42); }
    Vector2 GetLocalPos() { return pos; }

    void	MoveLocalPos(Vector2 Velocity) { pos += Velocity; }
    void	MoveWorldPos(Vector2 Velocity);
	
    void	SetLocalPos(Vector2 location) { pos = location; }
    void	SetLocalPosX(float location_x) { pos.x = location_x; }
    void	SetLocalPosY(float location_y) { pos.y = location_y; }
    void	SetWorldPos(Vector2 worldPos);
    void	SetWorldPosX(float worldPosX);
    void	SetWorldPosY(float worldPosY);

    /* 격발 */
    virtual void Fire(class obj_player* shooter);
    /* 탄을 움직임 */
    virtual void Update_Bullets();
    /* 탄의 충돌 처리 */
    bool collision_Bullets(class obj_player* target);
    bool collision_Bullets(std::vector<obj_weapon_bullet>& target_bullet, int damage);
    /* 탄을 그림 */
    virtual void Render_Bullets();
    /* 총의 상태를 출력 */
    void printStatus();
};
