#include "Actor.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter



Actor::Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Entity(createBody(world)),
    m_type(type),
    m_idleAnim(textures.get(Textures::Hero_Idle)),
    m_walkAnim(textures.get(Textures::Hero_Walk)),
    m_atEnd(false),
    m_isWalking(false)
{

    m_idleAnim.setFrameSize(sf::Vector2i(32, 30));
	m_idleAnim.setNumFrames(3);
	m_idleAnim.setDuration(sf::seconds(2.f));
	m_idleAnim.setRepeating(true);

	m_walkAnim.setFrameSize(sf::Vector2i(32, 30));
	m_walkAnim.setNumFrames(3);
	m_walkAnim.setDuration(sf::seconds(0.5f));
	m_walkAnim.setRepeating(false);

    // Player
    // TODO rendre adaptable taille anim (frame)
    sf::Rect<float> spriteBounds(0,0, m_walkAnim.getFrameSize().x, m_walkAnim.getFrameSize().y);// m_sprite.getGlobalBounds();
    Transformable::setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2FixtureDef ActorFixtureDef;
    b2PolygonShape ActorShape;
    ActorShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    ActorFixtureDef.shape = &ActorShape;
    ActorFixtureDef.density = 1.0f;
    ActorFixtureDef.friction = 0.8f;
    ActorFixtureDef.userData = this;
    m_body->CreateFixture(&ActorFixtureDef);
}


void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_isWalking)
        target.draw(m_walkAnim, states);
    else
        target.draw(m_idleAnim, states);

}

void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // TODO
    if(m_isWalking)
    {
        m_walkAnim.update(dt);

        if(m_walkAnim.isFinished())
        {
            m_isWalking = false;
            m_walkAnim.restart();
        }
    }
    else
    {
        m_idleAnim.update(dt);
    }


    Entity::updateCurrent(dt, commands);

}

bool Actor::isDestroyed() const
{
    return false;
}

unsigned int Actor::getCategory() const
{
    switch(m_type)
    {
        case Hero:
            return Category::PlayerActor;
    }
}

b2Body* Actor::createBody(b2World& world)
{
    b2BodyDef ActorBodyDef;
    ActorBodyDef.type = b2_dynamicBody;
    ActorBodyDef.fixedRotation = true;
    ActorBodyDef.linearDamping = 5.5f;
    b2Body* body = world.CreateBody(&ActorBodyDef);

    return body;
}

void Actor::goForward()
{
    float angle = Utility::pi() * getRotation() / 180.f;
    m_body->ApplyForce(b2Vec2(-sinf(angle) * 90 , cosf(angle) * 90 ), m_body->GetWorldCenter()); // cos et sin inversés et sin négatif car coordonnées sfml inversées (x, -y)

    m_isWalking = true;
}

void Actor::goBackward()
{
    float angle = Utility::pi() * getRotation() / 180.f;
    m_body->ApplyForce(b2Vec2(sinf(angle) * 50 , -cosf(angle) * 50 ), m_body->GetWorldCenter()); // cos et sin inversés et sin négatif car coordonnées sfml inversées (x, -y)
    m_isWalking = true;
}
void Actor::turnLeft()
{
    Entity::setRotation(- 5.f);
}

void Actor::turnRight()
{
    Entity::setRotation(5.f);
}

bool Actor::hasReachedEnd() const
{
    return m_atEnd;
}
void Actor::setReachedEnd(bool atEnd)
{
    m_atEnd = atEnd;
}

