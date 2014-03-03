#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"

class GameoverState : public State
{
        public:
                                        GameoverState(StateStack& stack, Context context);
            virtual                     ~GameoverState();
            virtual void                draw();
            virtual bool                update(sf::Time dt);
            virtual bool                handleEvent(const sf::Event& event);

        private:
            sf::Sprite                  m_backgroundSprite;
            sf::Text                    m_gameoverText;
            sf::Text                    m_instructionText;
};

#endif // GAMEOVERSTATE_H
