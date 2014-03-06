#ifndef ENDZONE_H
#define ENDZONE_H

#include "Entity.h"


class EndZone : public Entity
{
    public:
                                    EndZone(const TextureHolder& textures, const FontHolder& fonts, float width, float height, b2Body* body);
        virtual unsigned int        getCategory() const;
        virtual bool                isDestroyed() const;

    private:
        private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        static b2Body*          createBody(b2World& world);
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        sf::RectangleShape      m_shape;
};

#endif // ENDZONE_H
