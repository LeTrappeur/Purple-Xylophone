#ifndef STATE_H
#define STATE_H

#include "ResourceHolder.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace States
{
    enum ID
    {
        None,
        Title,
        Menu,
        Game,
        Loading,
        Pause,
        Gameover,
    };
}

namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;
class MusicPlayer;
class SoundPlayer;

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

        struct Context
        {
            Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sounds);

            sf::RenderWindow*           window;
            TextureHolder*              textures;
            FontHolder*                 fonts;
            Player*                     player;
            MusicPlayer*                music;
            SoundPlayer*                sounds;
        };

    public:
                                State(StateStack& stack, Context context);
    virtual                     ~State();

    virtual void                draw() = 0;
    virtual bool                update(sf::Time dt) = 0;
    virtual bool                handleEvent(const sf::Event& event) = 0;


    protected:
        void                    requestStackPush(States::ID stateID);
        void                    requestStackPop();
        void                    requestStateClear();

        Context                 getContext() const;

    private:
        StateStack*             m_stack;
        Context                 m_context;
};

#endif // STATE_H
