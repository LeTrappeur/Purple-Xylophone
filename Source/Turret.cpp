#include "Turret.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter
// TODO déterminer le type de rayon de la tourelle ainsi que son déplacement

Textures::ID toTextureID(Turret::Type type)
{
    switch (type)
    {
        case Turret::Blue:
            return Textures::Turret_B;

        case Turret::Red:
            return Textures::Turret_R;
    }
}

sf::Color toColor(Turret::Type type)
{
    switch (type)
    {
        case Turret::Blue:
            return sf::Color(0, 128, 192, 100);

        case Turret::Red:
            return sf::Color(255, 0, 0, 100);
    }
}

Turret::Turret(Type type, const TextureHolder& textures, const FontHolder& fonts, float radius, b2Body* body) :
    Entity(body),
    m_type(type),
    m_idleAnim(textures.get(toTextureID(type))),
    m_radius(radius),
    m_detectRadius(radius)
{

    m_idleAnim.setFrameSize(sf::Vector2i(40, 40));
	m_idleAnim.setNumFrames(3);
	m_idleAnim.setDuration(sf::seconds(2.f));
	m_idleAnim.setRepeating(true);

    sf::Rect<float> spriteBounds(0, 0, m_idleAnim.getFrameSize().x, m_idleAnim.getFrameSize().y);
    Transformable::setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    // sensor rayon turret
    m_body->GetFixtureList()->SetUserData(this);
    m_body->GetFixtureList()->SetSensor(true);

    // body turret
    b2FixtureDef TurretFixtureDef;
    b2PolygonShape TurretShape;
    TurretShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    TurretFixtureDef.shape = &TurretShape;
    TurretFixtureDef.density = 1.0f;
    TurretFixtureDef.userData = this;
    m_body->CreateFixture(&TurretFixtureDef);

    // radius
    m_detectRadius.setOrigin(m_radius ,m_radius);
    m_detectRadius.setPosition(getOrigin());
    m_detectRadius.setFillColor(toColor(type));
}

void Turret::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_detectRadius, states);
    target.draw(m_idleAnim, states);
}

void Turret::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // TODO
    m_idleAnim.update(dt);
    Entity::updateCurrent(dt, commands);
}

bool Turret::isDestroyed() const
{
    return false;
}

unsigned int Turret::getCategory() const
{

    return Category::Turret;
}
