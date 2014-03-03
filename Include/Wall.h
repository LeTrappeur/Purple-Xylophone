#ifndef PLATFORM_H
#define PLATFORM_H

#include <Box2D/Box2D.h>

#include "Entity.h"

class Wall : public Entity
{
    public:
        explicit                Wall(int width, int height, b2Body* body);
        virtual unsigned int    getCategory() const;

};

#endif // PLATFORM_H
