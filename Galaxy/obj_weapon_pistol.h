#pragma once

class obj_weapon_pistol : public  obj_weapon_prototype
{
private:

public:
    obj_weapon_pistol();
    void Render() override;
    void Render_Bullets() override;
    
    void Fire(class obj_player* shooter) override;
};