#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"
#include "ResourceHolder.h"
#include "TextNode.h"
#include "Animation.h"
#include "ColorCategory.h"

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
        virtual bool            isMarkedForRemoval() const;

        void                    goForward();
        void                    goBackward();
        void                    turnLeft();
        void                    turnRight();

        bool                    hasReachedEnd() const;
        void                    setReachedEnd(bool atEnd);

        void                    setColorCategory(unsigned int color);
        unsigned int            getColorCategory() const;

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        static b2Body*          createBody(b2World& world);
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
   private:
        Type                    m_type;

        Animation               m_currentAnim;
        Animation               m_walkAnim;
        Animation               m_idleAnim;

        bool                    m_atEnd;
        bool                    m_isWalking;
        bool                    m_isDetected;

        int                     m_power;

        unsigned int            m_suitColor;
};


#endif // ACTOR_H
