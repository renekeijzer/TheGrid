#include "NonCopyable.hpp"
#include "BaseEvent.hpp"

class EventManager : NonCopyable {
public:
	EventManager();
	virtual ~EventManager();

	template <typename E, typename Receiver>
	void subscribe(Receiver &receiver) {
		void (Receiver::*receive)(const E &) = &Receiver::receive;
		auto sig = signalFor(E::family());
		auto wrapper = EventCallbackWrapper<E>(std::bind(receive, &receiver, std::placeholders::_1));
		auto connection = sig->connect(wrapper);
		BaseReceiver &base = receiver;
		base.connections.push_back(std::make_pair(EventSignalWeakPtr(sig), connection));
	}

	void emit(const BaseEvent &event);

	template <typename E>
	void emit(std::unique_ptr<E> event) {
		auto sig = signalFor(E::family());
		BaseEvent *base = event.get();
		sig->emit(base);
	}

	template <typename E, typename ... Args>
	void emit(Args && ... args) {
		E event = E(std::forward<Args>(args) ...);
		auto sig = signalFor(std::size_t(E::family()));
		BaseEvent *base = &event;
		sig->emit(base);
	}

	std::size_t connectedReceivers() const {
		std::size_t size = 0;
		for (EventSignalPtr handler : handlers) {
			if (handler) size += handler->size();
		}
		return size;
	}

private:
	EventSignalPtr &signalFor(std::size_t id) {
		if (id >= handlers.size())
			handlers.resize(id + 1);
		if (!handlers[id])
			handlers[id] = std::make_shared<EventSignal>();
		return handlers[id];
	}

	template <typename E>
	struct EventCallbackWrapper {
		EventCallbackWrapper(std::function<void(const E &)> callback) : callback(callback) {}
		void operator()(const BaseEvent* event) { callback(*(static_cast<const E*>(event))); }
		std::function<void(const E &)> callback;
	};

	std::vector<EventSignalPtr> handlers;
};
