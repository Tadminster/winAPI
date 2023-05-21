#pragma once

class obj_chargingBar : public obj_rect
{
private:
    class sys_textOut* textout;

public:
    obj_chargingBar(class obj_prototype* player);
    ~obj_chargingBar();

    /* 그려질 수치, 최대수치, 좌표*/
    void Update(float value_cur, float value_max, Vector2 worldPos);
    virtual void Render() override;
};
