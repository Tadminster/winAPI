#include "framework.h"
#include "obj_circle.h"

obj_circle::obj_circle()
{
    for (int i = 0; i < 360; i++)
    {
        //            중점         멀어진 길이
        vertex[i].x = cosf(i*ToRadian);
        vertex[i].y = sinf(i*ToRadian);
    }
}

void obj_circle::Render()
{
    Vector2 TransformVertex[360];
    for (int i = 0; i < 360; i++)
    {

        //                      vector * M
        TransformVertex[i] = Vector2::Transform(vertex[i], W);

    }

    MoveToEx(g_hdc, TransformVertex[0].x, TransformVertex[0].y, nullptr);
    for (int i = 1; i < 360; i++)
        LineTo(g_hdc, TransformVertex[i].x, TransformVertex[i].y);
    LineTo(g_hdc, TransformVertex[0].x, TransformVertex[0].y);
}
