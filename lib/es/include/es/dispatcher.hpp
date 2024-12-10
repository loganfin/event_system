#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <vector>

namespace es {

class Dispatcher {
public:
    void start(std::function<void()> handler = {});

    template <typename T> void subscribe(std::function<void(T const&)> handler)
    {
        handlers_.push_back(handler);
    }

    template <typename T, typename... Args> void publish(Args... args)
    {
        using TCallback = std::function<void(T const&)>;

        // Create an event and pass const& to all subscribed handlers
        auto event = T(args...);

        for (auto& handler : handlers_) {
            if (handler.type() == typeid(TCallback)) {
                std::cout << "Calling handler\n";
                std::any_cast<TCallback>(handler)(event);
            } else {
                std::cout << "Handler doesn't match\n";
            }
        }
    }

private:
    std::vector<std::any> handlers_;
};

} // namespace es
