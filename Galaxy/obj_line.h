#pragma once
class obj_line : public obj_prototype
{
private:
	Vector2 vertex[2];

public:
	obj_line();
	void Render() override;
};

