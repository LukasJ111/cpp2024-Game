#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{

    return SDL_HasIntersection(&recA, &recB);

}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if(AABB(colA.collider, colB.collider))
    {
        //std::cout<< colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}
