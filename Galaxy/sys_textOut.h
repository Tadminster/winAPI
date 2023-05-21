#pragma once

class sys_textOut
{
public:
    Vector2 Pos;
    std::string target_text;

    sys_textOut() = default;
    void Update(Vector2 pos, std::string& str);
    void Render();
};
