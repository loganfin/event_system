#pragma once

#include "es/event.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace es {

class Dispatcher {
public:
    void start(std::function<void()> handler);

    template <typename EventType>
        requires(std::derived_from<EventType, Event>)
    void subscribe(std::function<void(EventType const&)> const& handler)
    {
        auto& handlers = get_handlers<EventType>();

        handlers.push_back([handler](Event const& event) {
            handler(static_cast<EventType const&>(event));
        });
    }

    template <typename EventType, typename... Args>
        requires(std::derived_from<EventType, Event>)
    void publish(Args&&... args)
    {
        auto event = EventType{std::forward<Args>(args)...};

        auto& handlers = get_handlers<EventType>();

        for (auto& handler : handlers) {
            handler(event);
        }
    }

private:
    std::unordered_map<
        std::type_index,
        std::vector<std::function<void(Event const&)>>>
        handlers_;

    template <typename EventType>
        requires(std::derived_from<EventType, Event>)
    std::vector<std::function<void(Event const&)>>& get_handlers()
    {
        auto type = std::type_index(typeid(EventType));

        if (handlers_.find(type) == handlers_.end()) {
            handlers_[type] = std::vector<std::function<void(Event const&)>>{};
        }

        return handlers_[type];
    }
};

} // namespace es
