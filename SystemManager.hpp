#pragma once
#include <memory>
#include <unordered_map>

#include "BaseSystem.hpp"
#include "System.hpp"
#include "EntityManager.hpp"
#include "NonCopyable.hpp"

#ifdef SYSTEM
class SystemManager : public NonCopyable
{
public:
	SystemManager(EntityManager & em) : entityManager(em){
	}
	
	template<typename S>
	void addSystem(std::shared_ptr<S> system){
		systems.insert(std::make_pair(S::family(), system));
	}

	template<typename S, typename ... Args>
	std::shared_ptr<S> addSystem(Args && ... args){ 
		std::shared_ptr<S> sys(new S(std::forward<Args>(args) ...));
		addSystem(sys);
		return sys;
	}

	template <typename S>
	std::shared_ptr<S> find() {
		auto it = systems.find(S::family());
		return it == systems.end()	? std::shared_ptr<S>() : std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
	}
	template <typename S>
	void update(double dt) {
		assert(init && "SystemManager::configure() not called");
		std::shared_ptr<S> s = find<S>();
		s->update(entityManager, dt);
	}

	void configure();
private:
#ifdef ANALYTICS
	friend class Analytics;
#endif	
	bool init = false;
	EntityManager & entityManager;
	std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> systems;
};

#endif