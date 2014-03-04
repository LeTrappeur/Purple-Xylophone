#include "MyContactListener.h"

#include "Entity.h"
#include "Actor.h"

MyContactListener::MyContactListener(CommandQueue& commandQueue):
    m_commandQueue(commandQueue),
    SENSOR_FLAG(false)
{}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    SENSOR_FLAG = false;
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
        SENSOR_FLAG = true;

    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::PlayerActor, Category::Turret) && SENSOR_FLAG)
    {
        std::cout << "Entering zone !" << std::endl;
    }
}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());

    SENSOR_FLAG = false;
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
        SENSOR_FLAG = true;

    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::PlayerActor, Category::Turret) && SENSOR_FLAG)
    {
        std::cout << "Leaving zone !" << std::endl;
    }
}

bool MyContactListener::matchesCategory(std::pair<Entity*,Entity*>& entities, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = entities.first->getCategory();
    unsigned int category2 = entities.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if(type1 & category2 && type2 & category1)
    {
        std::swap(entities.first, entities.second);
        return true;
    }
    else
    {
        return false;
    }
}
