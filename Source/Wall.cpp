#include "Wall.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


Wall::Wall(int width, int height, b2Body* body):
    Entity(body)
{
    m_body->GetFixtureList()->SetUserData(this);
}

unsigned int Wall::getCategory() const
{
    return Category::LowerScene;
}
