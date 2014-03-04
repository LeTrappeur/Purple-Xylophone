#ifndef TURRET_H
#define TURRET_H

#include "Entity.h"


class Turret : public Entity
{
    public:
        enum Type
        {
            Blue,
            Red,
        };
    public:
                                    Turret(Type type, const TextureHolder& textures, const FontHolder& fonts, float radius, b2Body* body);
        virtual unsigned int        getCategory() const;
        virtual bool                isDestroyed() const;

    private:
        private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        static b2Body*          createBody(b2World& world);
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        Type                    m_type;
        sf::Sprite              m_sprite;
        sf::CircleShape         m_detectRadius;
        float                   m_radius;
};

#endif // TURRET_H
