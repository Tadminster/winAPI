#pragma once
#include <windows.h>
#include <chrono>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>

#include "../Libs/DirectXTK/SimpleMath.h"
using namespace DirectX::SimpleMath;

#include "Types.h"
#include "sys_input.h"
#include "sys_timer.h"
#include "sys_random.h"
#include "sys_textOut.h"

#include "obj_prototype.h"
#include "obj_circle.h"
#include "obj_rect.h"
#include "obj_star.h"
#include "obj_line.h"

#include "obj_player.h"
#include "obj_chargingBar.h"

#include "obj_weapon_bullet.h"
#include "obj_weapon_prototype.h"
#include "obj_weapon_pistol.h"
#include "obj_weapon_shotgun.h"
#include "obj_weapon_sniper.h"

#define PI 3.141592f
#define ToRadian (PI/180.0f)
#define INPUT sys_input::GetInstance()
#define TIMER sys_timer::GetInstance()
#define DELTA sys_timer::GetInstance()->GetDelta()
#define RANDOM sys_random::GetInstance()

#define	UP					Vector2(0.0f,-1.0f)
#define	DOWN				Vector2(0.0f,1.0f)
#define	LEFT				Vector2(-1.0f,0.0f)
#define	RIGHT				Vector2(1.0f, 0.0f)

#define OFFSET_N            Vector2(0.0f, 0.0f)
#define OFFSET_L            Vector2(0.5f, 0.0f)
#define OFFSET_R            Vector2(-0.5f, 0.0f)
#define OFFSET_B            Vector2(0.0f, -0.5f)
#define OFFSET_T            Vector2(0.0f, 0.5f)
#define OFFSET_LB           Vector2(0.5f, -0.5f)
#define OFFSET_RB           Vector2(-0.5f, -0.5f)
#define OFFSET_LT           Vector2(0.5f, 0.5f)
#define OFFSET_RT           Vector2(-0.5f, 0.5f)

extern HINSTANCE			g_hInst;
extern HWND					g_hwnd;
extern class Main*          g_main;
extern HDC                  g_frontHdc;
extern HDC					g_hdc;
