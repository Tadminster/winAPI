#include "framework.h"
#include "sys_random.h"

sys_random::sys_random()
{
    std::random_device rd;
    randomEngine = new std::default_random_engine(rd());
}

sys_random::~sys_random()
{
    delete randomEngine;
}

int sys_random::Int(int min, int max)
{
    std::uniform_int_distribution<int> result(min, max);

    return result(*randomEngine);
}

float sys_random::Float(float min, float max)
{
    std::uniform_real_distribution<float> result(min, max);

    return result(*randomEngine);
}
