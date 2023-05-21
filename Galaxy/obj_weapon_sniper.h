#pragma once

class obj_weapon_sniper : public  obj_weapon_prototype
{
private:
    Vector2 vertex[2];  // 총의 모양
    //std::vector<Object_Weapon_Bullet> bullets;  //발사된 총알

    public:
    obj_weapon_sniper();
    void Render() override;
    void Fire(class obj_player* shooter) override;
};