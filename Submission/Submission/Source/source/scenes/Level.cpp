#include "Level.h" 
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/Movement.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_bullet_movement.h"
#include "../components/cmp_zombie.h"
#include"../components/cmp_zombie_movement.h"
#include "../components/player.h"
#include <iostream>
#include <thread>
 

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
vector<shared_ptr<Entity>> zombies;
float fire_time = 0.0f;
int zombie_count = zombies.size();
float spawn_time = 0.0f;
float i = 100.f;
int wave = 1;
int lefttospawn = 1;
float TimeSinceHit = 0.f;
void Level::Load()
{
	//creates initial player
	player = makeEntity();
	player->setPosition(Vector2f(200.0f, 100.0f));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(20.0f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(10.0f, 15.0f);
	player->addComponent<MovementComponent>();
	player->addComponent<PlayerComponent>();
	player->addTag("player");
}

void Level::Unload()
{
	player.reset();
	Scene::Unload(); 
}

void Level::Update(const double& dt)
{

	sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
    }
	//keeps count of number of spawned zombies
	zombie_count = zombies.size();
	//used to determine if new bullet should be created
	bool bulletfired = false;
	//Checks if sufficient time between shots are met
	if (Keyboard::isKeyPressed(Keyboard::S) && fire_time <= 0.0f)
	{
		bulletfired = true;
		fire_time = 0.3;
	}
	//creates each bullet
	if (bulletfired)
	{
		auto bullet = makeEntity();
		bullet->setPosition(player->getPosition());
		bullet->addComponent<BulletComponent>();
		bullet->addComponent<BulletMovement>();
		bullet->addTag("bullet");
		auto b = bullet->addComponent<ShapeComponent>();
		b->setShape<sf::CircleShape>(5.0f);
		b->getShape().setFillColor(Color::Yellow);
		b->getShape().setOrigin(10.0f, 15.0f);
	}
	//makes sure too many zombies aren't spawned at one time
	if (zombie_count <= 10 && spawn_time <= 0.0f && lefttospawn != 0)
	{
		//creates zombie and adds to list that are on screen
		shared_ptr<Entity> zombie = makeEntity();
		zombie->setPosition(Vector2f(600.f, i));
		auto z = zombie->addComponent<ShapeComponent>();
		z->setShape<sf::CircleShape>(15.0f);
		z->getShape().setFillColor(Color::Green);
		z->getShape().setOrigin(10.f, 15.f);
		zombie->addComponent<ZombieComponent>();
		zombie->addComponent<ZombieMovement>();
		zombie->addTag("zombie");
		zombies.push_back(zombie);
		//resets time until next spawn
		spawn_time = 0.3f;
		i = i + 100;
		lefttospawn = lefttospawn - 1;
	}
	int zombieID = 0;
	auto play = player->get_components<ShapeComponent>();
	auto play_health = player->get_components<PlayerComponent>();
	auto zombie_list = ents.find("zombie");
	auto bullet_list = ents.find("bullet");
	for (auto &e : zombie_list)
	{
		auto zom = e->get_components<ShapeComponent>();
		auto mov = e->get_components<ZombieMovement>();
		float horizontal = 0.f;
		float vertical = 0.f;
		float dist_hor = player->getPosition().x - e->getPosition().x;
		float dist_vert = player->getPosition().y - e->getPosition().y;
		if (dist_hor < 0)
			horizontal--;
		else if (dist_hor > 0)
			horizontal++;
		if (dist_vert < 0)
			vertical--;
		else if (dist_vert > 0)
			vertical++;
		mov[0]->move(horizontal *0.5, vertical *0.5);
		for (auto &b : bullet_list)
		{
			auto bul = b->get_components<ShapeComponent>();
			if (bul[0]->getShape().getGlobalBounds().intersects(zom[0]->getShape().getGlobalBounds()))
			{
				e->setForDelete();
				b->setForDelete();
				zombies.erase(zombies.begin() + zombieID);
			}
		}
		if (play[0]->getShape().getGlobalBounds().intersects(zom[0]->getShape().getGlobalBounds()) && TimeSinceHit >= 0.5f)
		{
			play_health[0]->isHit();
			TimeSinceHit = 0.f;
			play[0]->getShape().setFillColor(Color::Blue);
		}
		zombieID++;
	}
	if (play_health[0]->death())
	{
		Engine::GetWindow().close();
	}
	if (TimeSinceHit >= 0.1f)
		play[0]->getShape().setFillColor(Color::Red);
	if (lefttospawn == 0 && zombies.size() == 0)
	{
		wave = wave + 1;
		lefttospawn = 5 * wave;
		i = 0;
		cout << wave << endl;
	}
	spawn_time -= dt;
	fire_time -= dt;
	TimeSinceHit += dt;
	Scene::Update(dt);
}

void Level::Render()
{
	Scene::Render();
}