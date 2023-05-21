#pragma once
class sys_timer : public Singleton<sys_timer>
{
private:
    std::chrono::steady_clock::time_point    currentTime;
    std::chrono::steady_clock::time_point    lastTime;


    UINT                                framePerSecond;
    UINT                                framePerSecondCount;
    float                               framePerSecondTimeElapsed;
    float                               deltaTime;
    float                               deltaScaleTime;
    float                               worldTime;

public:
    sys_timer();
    bool    GetTick(float& time, float interval);
    void    Chronometry(UINT lock = 60);
    float   GetDelta() { return deltaTime; } //매크로 X
    float   GetDeltaTime() { return deltaScaleTime; }
    UINT    GetFramePerSecond() { return framePerSecond; }
    float   GetWorldTime() { return worldTime; }
};
