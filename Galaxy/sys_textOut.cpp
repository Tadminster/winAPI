#include "framework.h"
#include "sys_textOut.h"

#include <string>

void sys_textOut::Update(Vector2 pos, std::string& str)
{
    this->Pos = pos;
    target_text = str;
}

void sys_textOut::Render()
{
    TextOutA
    (
        g_hdc,
        static_cast<int>(this->Pos.x),
        static_cast<int>(this->Pos.y - 25.f),
        this->target_text.c_str(),
        static_cast<int>(this->target_text.size())
    );
}
