#include "State.h"
#include "StateStack.h"


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sounds):
    window(&window),
    textures(&textures),
    fonts(&fonts),
    player(&player),
    music(&music),
    sounds(&sounds)
{}

State::State(StateStack& stack, Context context):
    m_stack(&stack),
    m_context(context)
{}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    m_stack->pushState(stateID);
}

void State::requestStackPop()
{
    m_stack->popState();
}

void State::requestStateClear()
{
    m_stack->clearStates();
}

State::Context State::getContext() const
{
    return m_context;
}
