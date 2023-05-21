#pragma once
class obj_rect : public obj_prototype
{
private:
    Vector2 vertex[4];

public:
    obj_rect();
    virtual void Render() override;
};

