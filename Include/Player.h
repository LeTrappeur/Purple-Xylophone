#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Command.h"
#include "CommandQueue.h"

#include "Actor.h"

class Player
{
    public:
        enum Action
        {
            GoForward,
            GoBackward,
            TurnLeft,
            TurnRight,
            SetRed,
            SetGreen,
            SetBlue,
            ActionCount,
        };

        enum GameStatus
		{
			LevelRunning,
			LevelSuccess,
			LevelFailure,
			LevelAllSuccess,
		};

    public:
        explicit                                Player();
        void                                    handleEvent(const sf::Event& event, CommandQueue& commands);
        void                                    handleRealTimeInput(CommandQueue& commands);
        void                                    updateMouseWorldPosition(const sf::Vector2f& pos);

        void                                    assignKey(Action action, sf::Keyboard::Key key);
        void                                    assignKey(Action action, sf::Mouse::Button button);
        sf::Keyboard::Key                       getAssignedKey(Action action) const;
        // Retour template ? TODO
        //sf::Mouse::Button                       getAssignedKey(Action action) const;

        void 					                setGameStatus(GameStatus status);
		GameStatus 			                    getGameStatus() const;

        std::string                             getCurrentLevel() const;
        void                                    setCurrentLevel(const std::string& level);


    private:
        void                                    initializeActions();
        static bool                             isRealtimeAction(Action action);

    private:
        sf::Vector2f                            m_mouseWorldPos;
        std::map<sf::Keyboard::Key, Action>     m_keyBinding;
        std::map<sf::Mouse::Button, Action>     m_mouseBinding;
        std::map<Action, Command>               m_actionBinding;

        std::string                             m_currentLevel;
        GameStatus 							    m_currentGameStatus;
};

#endif // PLAYER_H
