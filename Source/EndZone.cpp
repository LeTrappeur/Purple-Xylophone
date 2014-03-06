#include "EndZone.h"

// Todo retient le nom du prochain niveau, prop dans Tiled

EndZone::EndZone(const TextureHolder& textures, const FontHolder& fonts, float width, float height, b2Body* body) :
    Entity(body),
    m_shape(sf::Vector2f(width, height))
{
    sf::Rect<float> spriteBounds = m_shape.getGlobalBounds();
    Transformable::setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    // sensor
    m_body->GetFixtureList()->SetUserData(this);
    m_body->GetFixtureList()->SetSensor(true);

    m_shape.setFillColor(sf::Color(0, 255, 0 ,100));
    m_shape.setOutlineThickness(1.f);
    m_shape.setOutlineColor(sf::Color(0, 255, 0 ,200));
}

void EndZone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void EndZone::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // TODO
    Entity::updateCurrent(dt, commands);
}

bool EndZone::isDestroyed() const
{
    return false;
}

unsigned int EndZone::getCategory() const
{
    return Category::EndZone;
}


