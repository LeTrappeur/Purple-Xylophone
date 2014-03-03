#include "Player.h"
#include "Actor.h"
Player::Player()
{
        // Set initial key bindings
        m_keyBinding[sf::Keyboard::Q] = GoLeft;
        m_keyBinding[sf::Keyboard::D] = GoRight;
        // Set initial action bindings
        initializeActions();

        for (auto it = m_actionBinding.begin(); it!= m_actionBinding.end(); ++it)
            (*it).second.category = Category::PlayerActor;

}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    // event souris
    if (event.type == sf::Event::KeyPressed)
    {
         auto found = m_keyBinding.find(event.key.code);
            if (found != m_keyBinding.end() && !isRealtimeAction(found->second))
                commands.push(m_actionBinding[found->second]);
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        auto found = m_mouseBinding.find(event.mouseButton.button);
            if (found != m_mouseBinding.end() && !isRealtimeAction(found->second))
                commands.push(m_actionBinding[found->second]);
    }
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for (auto it = m_keyBinding.begin(); it!= m_keyBinding.end(); ++it)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed((*it).first) && isRealtimeAction((*it).second))
            commands.push(m_actionBinding[(*it).second]);
    }

    // Check if mouse button are pressed
    for (auto it = m_mouseBinding.begin(); it!= m_mouseBinding.end(); ++it)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Mouse::isButtonPressed((*it).first) && isRealtimeAction((*it).second))
            commands.push(m_actionBinding[(*it).second]);
    }
}

void Player::updateMouseWorldPosition(const sf::Vector2f& pos)
{
    m_mouseWorldPos = pos;
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto it = m_keyBinding.begin(); it != m_keyBinding.end(); )
    {
        if (it->second == action)
            m_keyBinding.erase(it++);
        else
            ++it;
    }
    // Insert new binding
    m_keyBinding[key] = action;
}

void Player::assignKey(Action action, sf::Mouse::Button button)
{
    // Remove all keys that already map to action
    for (auto it = m_mouseBinding.begin(); it != m_mouseBinding.end(); )
    {
        if (it->second == action)
            m_mouseBinding.erase(it++);
        else
            ++it;
    }
    // Insert new binding
    m_mouseBinding[button] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for (auto it = m_keyBinding.begin(); it != m_keyBinding.end(); ++it )
    {
        if ((*it).second == action)
            return (*it).first;
    }
    return sf::Keyboard::Unknown;
}

// TODO mouse settings
//sf::Mouse::Button Player::getAssignedKey(Action action) const
//{
//    for (auto it = m_mouseBinding.begin(); it != m_mouseBinding.end(); ++it )
//    {
//        if ((*it).second == action)
//            return (*it).first;
//    }
//    return sf::Mouse::Button::Unknow;
//}

void Player::initializeActions()
{
        m_actionBinding[GoLeft].action  = derivedAction<Actor>([] (Actor& actor, sf::Time){});
        m_actionBinding[GoRight].action = derivedAction<Actor>([] (Actor& actor, sf::Time){});
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
            case GoLeft:
            case GoRight:
                    return true;

            default:
                    return false;
    }
}
