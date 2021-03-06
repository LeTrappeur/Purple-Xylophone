#ifndef TURRET_H
#define TURRET_H

#include "Entity.h"
#include "Animation.h"

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
        unsigned int                getColorCategory() const;

    private:
        private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        Type                    m_type;
        Animation               m_idleAnim;
        sf::CircleShape         m_detectRadius;
        float                   m_radius;

        unsigned int            m_turretColor;
};

#endif // TURRET_H
