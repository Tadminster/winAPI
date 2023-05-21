#include "framework.h"
#include "obj_line.h"

obj_line::obj_line()
{
    //local space
    vertex[0].x = 0;
    vertex[0].y = 0;

    vertex[1].x = 1;
    vertex[1].y = 0;
}

void obj_line::Render()
{
    Vector2 TransformVertex[2];
    for (int i = 0; i < 2; i++)
    {
        //world space
        TransformVertex[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_hdc, TransformVertex[0].x, TransformVertex[0].y, NULL);
    LineTo(g_hdc, TransformVertex[1].x, TransformVertex[1].y);

}
