#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent: public Component
{

public:
    Vector2D position;
    Vector2D velocity;

    // Originaliai buvo 32 ir 32, bet modifikavau atsizvelgiant i musu pixel arto dydi
    int height = 16;
    int width = 16;
    int scale = 1;

    int speed=3;

    void init() override
    {
        velocity.Zero();
    }

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(int sc)
    {
        position.x=400;
        position.y=320;
        scale = sc;
    }

    TransformComponent(float x, float y)
    {
        position.x=x;
        position.y=y;
    }

    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x=x;
        position.y=y;
        height=h;
        width=w;
        scale=sc;
    }

    void update() override
    {
        position.x+=velocity.x*speed;
        position.y+=velocity.y*speed;
    }

};

