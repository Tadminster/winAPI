#pragma once
class obj_star : public obj_prototype
{
private:
	Vector2 vertex[5];

public:
	obj_star();
	void Render() override;

	void set_fire();
	bool get_fire() const;
};

