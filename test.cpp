#include <iostream>

#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "Analytics.hpp"
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

struct movedEvent : Event<movedEvent>{
public:
	explicit movedEvent(Entity & en) : ent(ent){}
	Entity & ent;
};

struct movementSystem : System<movementSystem>{
	void update(EntityManager & entities, EventManager & events, double dt){
		
		for (Entity & ent : entities.withComponents<Position, Velocity>()){
			Position::Handle &pos = ent.getComponent<Position>();
			Velocity::Handle &vel = ent.getComponent<Velocity>();
			
		}
	}
};

class controllerSystem : public System<controllerSystem>, public Receiver<controllerSystem>{
public:
	void configure(EventManager & events) override{
		events.subscribe<movedEvent>(*this);
	}	


	void update(EntityManager & entities, EventManager & events,  double dt)override{
		for (Entity & ent : entities.withComponents<Position>()){
			Position::Handle & pos = ent.getComponent<Position>();
		}
	}

	void receive(const movedEvent & event){
		std::cout << "Working sorta";
	}
};

/*
int main(){
	
	EntityManager em;
	EventManager ev;
	SystemManager sys(em, ev);

	Analytics * an = Analytics::get(em, sys, ev);

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
		an->log();
	}
}*/