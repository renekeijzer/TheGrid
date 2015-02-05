#include <iostream>

#include "EntityManager.hpp"
#include "SystemManager.hpp"


struct Position : Component<Position>{
	Position(int xp, int yp) : x(xp), y(yp){}
	int x;
	int y;

};

struct Velocity : Component<Velocity>{
	Velocity(int xp, int yp) : x(xp), y(yp){}
	int x;
	int y;

};

struct movementSystem : System<movementSystem>{
	void update(EntityManager & entities, double dt){
		int x = 0;
		for (Entity & ent : entities.withComponents<Position, Velocity>()){
			Position::Handle &pos = ent.getComponent<Position>();
			Velocity::Handle &vel = ent.getComponent<Velocity>();

			pos->x += vel->x;
			pos->y += vel->y;
		}
	}
};

struct controllerSystem : System<controllerSystem>{
	void update(EntityManager & entities, double dt){
		for (Entity & ent : entities.withComponents<Position>()){
			Position::Handle & pos = ent.getComponent<Position>();

			std::cout <<"Entity id = " << ent.getId().index() <<"\tx = " << pos->x << "\t y = " << pos->y << "\r\n";
		}
	}
};


int main(){
	
	EntityManager em;
	SystemManager sys(em);

	Entity en = em.createEntity();
	Position::Handle & pos = en.addComponent<Position>(20, 30);
	Velocity::Handle & vel = en.addComponent<Velocity>(2, 2);
	
	Entity en2 = em.createEntity();
	Position::Handle & pos2 = en2.addComponent<Position>( 40, 20);
	Velocity::Handle & vel2 = en2.addComponent<Velocity>(3, 3);


	std::cout << en.getId().index() << "\r\n";
	std::cout << en2.getId().index() << "\r\n";

	sys.addSystem<movementSystem>();
	sys.addSystem<controllerSystem>();
	sys.configure();

	double dt = 0;

	while (1){
		sys.update<movementSystem>(dt);
		sys.update<controllerSystem>(dt);
	}
}