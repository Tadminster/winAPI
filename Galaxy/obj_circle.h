#pragma once
class obj_circle : public obj_prototype
{
private:
	Vector2 vertex[360];

public:
	obj_circle();
	void Render() override;
};

