#pragma once

class obj_weapon_bullet : public obj_rect
{
protected:
   
public:
    Vector2         Pos_Current;            // 현재 위치(local)
    Vector2         Pos_Initial;            // 처음 발사된 위치
    int             Hp;                     // 체력
    Vector2         shooting_Dir;           // 방향
    float           speed;                  // 속도
    int             Damage;                 // 공격력
    float           range;                  // 사정거리
    float           traveledDistance;       // 이동거리
    float           pressPower;                 // 차지

    Vector2         gravityDir;             // 중력 방향
    float           gravityForce;           // 중력 힘
    float           gravityWeight;          // 중력 가중치

public:
    obj_weapon_bullet(Vector2 pos, Vector2 direction, float speed, float range, float charge);

    virtual void Update() override;
    virtual void Render() override;

    /* 탄이 이동한 거리가 range를 넘었는지 확인 */
    bool hasTraveledTooFar() const {return traveledDistance >= range;}
    bool hasIntersect(class obj_prototype* target) const;

    void reflection_y();
    void reflection_x();
};
