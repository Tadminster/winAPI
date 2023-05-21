#include "framework.h"
#include "obj_prototype.h"

obj_line* obj_prototype::axis = nullptr;
void obj_prototype::create_static_member()
{
	axis = new obj_line();
}

void obj_prototype::delete_static_member()
{
	delete axis;
}

obj_prototype::obj_prototype()
{
	pos.x = 0;
	pos.y = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	rotation2.x = 0.0f;
	rotation2.y = 0.0f;
	rotation2.z = 0.0f;

	P = nullptr;
	this->hasAxis = true;
	this->hasGauge_Charging = true;
}

obj_prototype::~obj_prototype()
= default;

void obj_prototype::Update()
{
	/*S._11 = scale.x;
	S._22 = scale.y;

	R._11 = cos(rotation * ToRadian);
	R._22 = cos(rotation * ToRadian);
	R._12 = -sin(rotation * ToRadian);
	R._21 = sin(rotation * ToRadian);

	T._41 = pos.x;
	T._42 = pos.y;
	T._43 = 0;*/

	Pi = Matrix::CreateTranslation(pivot.x, pivot.y,0.0f);
	S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	R2 = Matrix::CreateFromYawPitchRoll(rotation2.y, rotation2.x, rotation2.z);
	T = Matrix::CreateTranslation(pos.x, pos.y, 0.0f);

	RT = R * T * R2;
	

	//포인터에 주소값이 있다면
	if (P)
	{
		RT *= *P;
	}
	W = Pi * S * RT;
}

void obj_prototype::Render()
{
	if (hasAxis)
	{
		axis->set_worldPos(get_worldPos());
		axis->scale.x = scale.x * 2.0f;
		//         각도   =  단위벡터
		axis->rotation.z = atan2f(get_right().y, get_right().x);
		axis->Update();
		axis->Render();

		axis->scale.x = scale.y * 2.0f;
		axis->rotation.z = atan2f(get_up().y, get_up().x);
		axis->Update();
		axis->Render();
	}
}

Matrix& obj_prototype::get_RT()
{
	return this->RT;
}

void obj_prototype::move_worldPos(Vector2 velocity)
{
	if (!P)
	{
		pos += velocity;
	}
	else
	{
		Vector2 locVelocity = Vector2::TransformNormal(velocity, (*P).Invert());
		pos += locVelocity;
	}
}

void obj_prototype::set_worldPos(Vector2 worldPos)
{
	if (not P)
	{
		pos = worldPos;
	}
	else
	{
		Vector2 location = Vector2::Transform(worldPos, (*P).Invert());
		pos = location;
	}
}

void obj_prototype::set_worldPos_x(float worldPos_x)
{
	if (!P)
	{
		pos.x = worldPos_x;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(worldPos_x, 0), (*P).Invert());
		pos.x = location.x;
	}
}

void obj_prototype::set_worldPos_y(float worldPos_y)
{
	if (!P)
	{
		pos.y = worldPos_y;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(0, worldPos_y), (*P).Invert());
		pos.y = location.y;
	}
}
