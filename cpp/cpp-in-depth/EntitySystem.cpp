#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

enum class EntityType { Player, Enemy, Wall };

class Entity
{
protected:
	float x, y;
	bool isAlive = true;
public:
	Entity(float startX, float startY) : x(startX), y(startY) {}
	virtual void update(float dt) = 0;
	virtual void draw() = 0;
	bool getIsAlive() const { return isAlive;}
	void kill() { isAlive = false;}
	virtual ~Entity () {}
	float getX() const { return x;}
	float getY() const { return y;}
	virtual float getRadius() const = 0;
	virtual void collision(Entity& other) {}
	virtual EntityType getEntityType() const = 0;
};

class Player : public Entity
{
protected:
	float radius = 30;
public:
	Player(float startX, float startY) : Entity(startX, startY) {}
	void update(float dt) override 
	{
		x += 100.f * dt;
	}
	void draw() override
	{
		std::cout << "Player is at " << x << ", " << y << "\n";
	}
	float getRadius() const override { return radius; }
	void collision(Entity& other) override { std::cout << "Player collision! \n"; }
	EntityType getEntityType() const override { return EntityType::Player; }
	~Player() override
	{
		std::cout << "Player is destroyed. \n";
	}
};

class Enemy : public Entity
{
private:
	int life = 10;
protected:
	float radius = 30;
public:
	Enemy(float startX, float startY) : Entity(startX, startY) {}
	void update(float dt) override 
	{
		y += 100.f * dt;
		life -= 1;
		if (life <= 0)
		{
			kill();
		}
	}
	void draw() override
	{
		std::cout << "Enemy is at " << x << ", " << y << "\n";
	}
	float getRadius() const override { return radius; }
	void collision(Entity& other) override
	{
		if (other.getEntityType() == EntityType::Player)
		{
			std::cout << "Enemy got killed! \n";
			kill();
		}
		else if (other.getEntityType() == EntityType::Wall)
		{
			std::cout << "Enemy just hit a wall \n";
		}
	}
	EntityType getEntityType() const override { return EntityType::Enemy; }
	~Enemy() override
	{
		std::cout << "Enemy is destroyed. \n";
	}
};

class Wall : public Entity
{
public:
	Wall(float startX, float startY) : Entity(startX, startY) {}
	void update(float dt) override {}
	void draw() override
	{
		std::cout << "Wall is at " << x << ", " << y << "\n";
	}
	float getRadius() const override { return 0; }
	EntityType getEntityType() const override { return EntityType::Wall; }
	~Wall() override
	{
		std::cout << "Wall is destroyed. \n";
	}
};

int main()
{
	std::vector<std::unique_ptr<Entity>> entities;
	entities.push_back(std::make_unique<Player>(-400.f, 100.f));
	entities.push_back(std::make_unique<Player>(100.f, 0.f));
	entities.push_back(std::make_unique<Enemy>(0.f, -300.f));
	entities.push_back(std::make_unique<Enemy>(0.f, -0.f));
	entities.push_back(std::make_unique<Wall>(0.f, -100.f));

	for (int frame = 0; frame < 15; frame++)
	{
		std::cout << "FRAME: " << frame + 1 << "\n";
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->update(1.f);
		}
		for (size_t i = 0; i < entities.size(); i++)
		{
			for (size_t j = i + 1; j < entities.size(); j++)
			{
				float dx = entities[i]->getX() - entities[j]->getX();
				float dy = entities[i]->getY() - entities[j]->getY();
				float radiusSum = entities[i]->getRadius() + entities[j]->getRadius();
				if (dx * dx + dy * dy < radiusSum * radiusSum)
				{
					std::cout << "COLLISION! \n";
					entities[i]->collision(*entities[j]);
					entities[j]->collision(*entities[i]);
				}
			}
		}
		entities.erase(
			std::remove_if(entities.begin(), entities.end(),
				[](const std::unique_ptr<Entity>& e) { return !e->getIsAlive(); }),
			entities.end());
		if (std::any_of(entities.begin(), entities.end(),
			[](const std::unique_ptr<Entity>& e) {return e->getEntityType() == EntityType::Enemy; }) == false)
		{
			std::cout << "All enemies are dead, level completed \n";
			break;
		}

		std::sort(entities.begin(), entities.end(),
			[](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) { return a->getY() < b->getY(); });

		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->draw();
		}
	}
	auto it = std::find_if(entities.begin(), entities.end(),
		[](const std::unique_ptr<Entity>& e) {return e->getEntityType() == EntityType::Player; });

	if (it != entities.end())
	{
		std::cout << "Player found at " << (*it)->getX() << ", " << (*it)->getY() << "\n";
	}
	else
	{
		std::cout << "Player not found. \n";
	}
}
