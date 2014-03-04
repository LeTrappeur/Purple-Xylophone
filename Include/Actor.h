#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"
#include "ResourceHolder.h"
#include "TextNode.h"
#include "Animation.h"

class Actor : public Entity
{
    public:
        enum Type
        {
            Hero,
            Enemy,
            Allied,
        };

    public:
        explicit                Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        virtual unsigned int    getCategory() const;
        virtual bool            isDestroyed() const;

        void                    goForward();
        void                    goBackward();
        void                    turnLeft();
        void                    turnRight();

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        static b2Body*          createBody(b2World& world);

    protected:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);

    protected:
        Type                    m_type;

        sf::Sprite              m_sprite;
};


#endif // ACTOR_H
