#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <array>
#include <list>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include "MyContactListener.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"
#include "SceneNode.h"
#include "SoundPlayer.h"
#include "Actor.h"



class World
{
    private:
        enum Layer
        {
            Background,
            Foreground,
            LayerCount
        };
    public:
        explicit                                World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds);

        void                                    update(sf::Time dt);
        void                                    draw();

        CommandQueue&                           getCommandQueue();
        sf::Vector2f                            getMouseWorldPosition();


    private:
        void                                    loadTextures();
        void                                    buildScene();
        void                                    updateSounds();

    private:
        sf::RenderWindow&                       m_window;
        sf::View                                m_worldView;
        tmx::MapLoader                          ml;

        TextureHolder                           m_textures;
        FontHolder&                             m_fonts;
        SoundPlayer&                            m_sounds;

        b2World                                 m_physicWorld;
        MyContactListener                       m_contactListener;
        sf::FloatRect                           m_worldBounds;

        SceneNode m_sceneGraph;
        std::array<SceneNode*, LayerCount>      m_sceneLayers;

        Actor*                                  m_player;
        sf::Vector2f                            m_spawnPosition;

        CommandQueue                            m_commandQueue;
};

#endif // WORLD_H
