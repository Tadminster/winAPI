#pragma once
class obj_prototype
{
private:
	static class obj_line* axis;
public:
	static void create_static_member();
	static void delete_static_member();
	
protected:
	// Scale, Rotation, Translation
	Matrix Pi, S, R, R2, T, RT, W;
	Matrix* P;

public:
	Vector2 pivot;
	Vector2	scale;
	Vector2	pos;
	Vector3	rotation;	// 자전
	Vector3	rotation2;	// 공전
	bool	hasAxis;

	class obj_chargingBar* gauge_charging;
	bool	hasGauge_Charging;
	
	class obj_chargingBar* gauge_hp;
	bool	hasGauge_Hp;

public:
	obj_prototype();
	virtual ~obj_prototype();
	virtual void Update();
	virtual void Render();

	Matrix&		get_RT();
	void		set_parentRT(obj_prototype& src) { P = &src.RT; }
	void		set_parentT(obj_prototype& src) { P = &src.T; }
	
	Vector2 get_right() { return Vector2(RT._11, RT._12); }
	Vector2 get_up() { return Vector2(RT._21, RT._22); }
	Vector2 get_worldPos() { return Vector2(RT._41, RT._42); }
	Vector2 get_localPos() { return pos; }

	void	move_localPos(Vector2 velocity) { pos += velocity; }
	void	move_worldPos(Vector2 velocity);
	
	void	set_localPos(Vector2 location) { pos = location; }
	void	set_localPos_x(float location_x) { pos.x = location_x; }
	void	set_localPos_y(float location_y) { pos.y = location_y; }
	void	set_worldPos(Vector2 worldPos);
	void	set_worldPos_x(float worldPos_x);
	void	set_worldPos_y(float worldPos_y);
};

