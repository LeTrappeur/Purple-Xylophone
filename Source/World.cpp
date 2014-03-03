#include "World.h"

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include "Actor.h"
#include "SpriteNode.h"
#include "SoundNode.h"
#include "Wall.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

// TODO LEVEL
World::World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds):
    m_window(window),
    m_fonts(fonts),
    m_sounds(sounds),
    m_worldView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 0.0f)),
    m_worldBounds(
                  0,
                  0,
                  1024,
                  768
                  ),
    m_player(nullptr),
    m_spawnPosition(0 ,0),
    m_commandQueue(),
    m_contactListener(m_commandQueue),
    ml("maps/")
{
    loadTextures();

    m_worldView.setCenter(m_spawnPosition);

    m_physicWorld.SetContactListener(&m_contactListener);

    buildScene();
}

void World::loadTextures()
{

}

void World::buildScene()
{

    // Init layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Foreground) ? Category::UpperScene : Category::None;
        SceneNode::Ptr layer(new SceneNode(category));
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }
    // SoundNode
    std::unique_ptr<SoundNode> soundNode(new SoundNode(m_sounds));
    m_sceneGraph.attachChild(std::move(soundNode));


	ml.Load("map.tmx");
	const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
}

void World::update(sf::Time dt)
{
    while(!m_commandQueue.isEmpty())
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);


    m_physicWorld.Step(dt.asSeconds(), 8, 4);
    m_sceneGraph.update(dt, m_commandQueue);

    updateSounds();
    m_sceneGraph.removeWrecks();
}

sf::Vector2f World::getMouseWorldPosition()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos, m_worldView);
    return worldPos;
}

void World::draw()
{

    m_window.setView(m_worldView);
    m_window.draw(ml);
    m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return m_commandQueue;
}

void World::updateSounds()
{
   m_sounds.removeStoppedSounds();
}
