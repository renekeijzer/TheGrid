#include <iostream>

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Component.hpp"

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



int main(){
	
	EntityManager em;

	Entity en = em.createEntity();
	Position::Handle & pos = en.addComponent<Position>(20, 30);
	Velocity::Handle & vel = en.addComponent<Velocity>(2, 2);
	
	Entity en2 = em.createEntity();
	Position::Handle & pos2 = en2.addComponent<Position>( 40, 20);
	Velocity::Handle & vel2 = en2.addComponent<Velocity>(3, 3);

	while (1){
		std::cout << pos->x << " - " << pos->y << "\r\n";

		std::cout << pos2->x << " - " << pos2->y << "\r\n";
	}
}