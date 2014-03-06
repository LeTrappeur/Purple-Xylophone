#include "GameState.h"
#include "MusicPlayer.h"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , m_world(*context.window, *context.fonts, *context.sounds, context.player->getCurrentLevel())
    , m_player(*context.player)
{
    context.music->setVolume(5.f);
    //context.music->play(Music::GameTheme);
    m_player.setGameStatus(Player::LevelRunning);
    registerLevels();
}

void GameState::draw()
{
    m_world.draw();
}

bool GameState::update(sf::Time dt)
{
    m_world.update(dt);

    if(m_world.hasPlayerReachedEnd())
        goToNextLevel();

    CommandQueue& commands = m_world.getCommandQueue();

    m_player.handleRealTimeInput(commands);
    m_player.updateMouseWorldPosition(m_world.getMouseWorldPosition());

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    // Game input handling
    CommandQueue& commands = m_world.getCommandQueue();
    m_player.handleEvent(event, commands);

     //Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPush(States::Pause);
    }
    return true;
}

void GameState::goToNextLevel()
{
    auto it = std::find(m_levels.begin(), m_levels.end(), m_player.getCurrentLevel()); // Position du niveau en cours

    if(m_levels.back() == *it)
    {
        m_player.setGameStatus(Player::LevelAllSuccess); // fin du jeu
    }
    else
    {
        m_player.setGameStatus(Player::LevelSuccess);
        m_player.setCurrentLevel(*(++it)); // Niveau suivant
    }
    requestStackPush(States::Gameover);
}

void GameState::registerLevels()
{
    m_levels.push_back("level_1.tmx");
    m_levels.push_back("level_2.tmx");
}
