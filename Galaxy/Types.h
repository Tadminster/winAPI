#pragma once
//정수타입 좌표
struct Int2
{
	int x;
	int y;
	Int2() : x(0), y(0) {}
	Int2(int x, int y) : x(x), y(y) {}
};



template <typename T>
class Singleton
{
	//static
private:
	static T* instance;

public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	};

	//member
public:
	virtual ~Singleton() {};
	void DeleteSingleton()
	{
		delete instance;
		instance = nullptr;
	};
};

template <typename T>
T* Singleton<T>::instance = nullptr;

class Scene
{
public:
	//가상소멸자 (업캐스팅으로 객체 사용할떈 소멸자도 가상함수로 만들어야함)
	virtual ~Scene() {};
	//초기화
	virtual void Init() = 0;
	//해제
	virtual void Release() = 0;
	//Loop
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	//Window Resize
	virtual void ResizeScreen() = 0;
};