#pragma once
class obj_player : public obj_prototype
{
private:
    Vector2 vertex[360];
    int     hand;

public:
    int     Hp_current;
    int     Hp_max;
    int     move_speed;
    float   charge_current;
    float   charge_max;

public:
    obj_player();
    void        Update() override;
    void        Render() override;

    int         get_hand();
    void        set_hand(int type_Branch);

    Vector2     get_playerPos();


};

