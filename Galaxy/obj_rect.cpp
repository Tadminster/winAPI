#include "framework.h"
#include "obj_rect.h"

obj_rect::obj_rect()
{
    //local space
    vertex[0].x = 0 - 0.5f;
    vertex[0].y = 0 - 0.5f;

    vertex[1].x = 1 - 0.5f;
    vertex[1].y = 0 - 0.5f;

    vertex[2].x = 1 - 0.5f;
    vertex[2].y = 1 - 0.5f;

    vertex[3].x = 0 - 0.5f;
    vertex[3].y = 1 - 0.5f;
}

    void obj_rect::Render()
{
    obj_prototype::Render();
    
    Vector2 TransformVertex[4];
    for (int i = 0; i < 4; i++)
    {
        //                      vector * M
        TransformVertex[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_hdc, TransformVertex[0].x, TransformVertex[0].y, NULL);
    LineTo(g_hdc, TransformVertex[1].x, TransformVertex[1].y);
    LineTo(g_hdc, TransformVertex[2].x, TransformVertex[2].y);
    LineTo(g_hdc, TransformVertex[3].x, TransformVertex[3].y);
    LineTo(g_hdc, TransformVertex[0].x, TransformVertex[0].y);
}