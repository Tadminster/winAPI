#pragma once
class Main final : public Scene
{
	SYSTEMTIME system_time;

	obj_player* player[2];
	int numOfPlayer = std::size(player);

	sys_textOut* time_remaining;
	float turnTime;
	int turn;
	// obj_line* front_line;
	// obj_star* star;

	obj_weapon_prototype* w_prototype;
	
	obj_weapon_pistol* pistol[2];
	obj_weapon_shotgun* shotgun[2];
	obj_weapon_sniper* sniper[2];
	//Object_Line* line_planet[8];
	//Object_Circle* planet[8];
	
	//Object_Line* line_satellite[6];
	//Object_Circle* satellite[6];
	
	//Object_Line* line_star[16];
	//Object_Weapon_Bullet* bullet;
public:
	Main();
	~Main();

	void Init()			override;
	void Release()		override;	//해제
	void Update()		override;
	void LateUpdate()	override;	//갱신
	void Render()		override;
	void ResizeScreen() override;

};

