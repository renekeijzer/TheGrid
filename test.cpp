#include <iostream>

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Component.hpp"
#include "System.hpp"
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
		std::cout << "movementsystem call \r\n";
	}
};

struct controllerSystem : System<controllerSystem>{
	void update(EntityManager & entities, double dt){
		std::cout << "controllertsystem call \r\n";
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


	sys.addSystem<movementSystem>();
	sys.addSystem<controllerSystem>();
	sys.configure();

	double dt = 0;

	while (1){
		sys.update<movementSystem>(dt);
		sys.update<controllerSystem>(dt);
	}
}