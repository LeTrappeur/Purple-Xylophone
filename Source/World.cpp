#include "World.h"

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include "Actor.h"
#include "SpriteNode.h"
#include "SoundNode.h"
#include "Wall.h"
#include "Turret.h"

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
    m_spawnPosition(1024/2 ,768/2),
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
    m_textures.load(Textures::Hero, "player.png");
    m_textures.load(Textures::Turret_B, "blue_turret.png");
    m_textures.load(Textures::Turret_R, "red_turret.png");
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
    for (const auto& l : layers)
	{
		if (l.name == "Static") //static bodies which make up the map geometry
		{
			for (const auto& o : l.objects)
			{
				std::cout << o.GetName() << " at: " << o.GetPosition().x << " " << o.GetPosition().y << " size: " << o.GetAABB().width << " " << o.GetAABB().height << std::endl;
                std::unique_ptr<Wall> wall(new Wall(o.GetAABB().width, o.GetAABB().height, tmx::BodyCreator::Add(o, m_physicWorld)));
                wall->setPosition(o.GetCentre());
                m_sceneLayers[Layer::Foreground]->attachChild(std::move(wall));
			}
		}
		if (l.name == "Turrets")
		{
			for (const auto& o : l.objects)
			{
			    std::cout << o.GetName() << " at: " << o.GetPosition().x << " " << o.GetPosition().y << " size: " << o.GetAABB().width << " " << o.GetAABB().height << std::endl;
                std::unique_ptr<Turret> turret(new Turret(Turret::Red, m_textures, m_fonts, o.GetAABB().width, tmx::BodyCreator::Add(o, m_physicWorld)));
                turret->setPosition(o.GetCentre());
                m_sceneLayers[Layer::Foreground]->attachChild(std::move(turret));
			}
		}
	}

    std::cout << "Creating player" << std::endl;
	std::unique_ptr<Actor> player(new Actor(Actor::Hero, m_textures, m_fonts, m_physicWorld));
	m_player = player.get();
	player->setPosition(m_spawnPosition);
	m_sceneLayers[Layer::Foreground]->attachChild(std::move(player));
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
    m_worldView.setCenter(m_player->getPosition());
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
