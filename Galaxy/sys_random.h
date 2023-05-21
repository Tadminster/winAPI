#pragma once

class sys_random : public Singleton<sys_random>
{
private:
    std::default_random_engine* randomEngine;

public:
    sys_random();
    ~sys_random();
    int Int(int min = 0, int max = 1);
    float Float(float min = 0.0f, float max = 1.0f);
};

