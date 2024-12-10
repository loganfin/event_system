#include "es/dispatcher.hpp"

namespace es {

void Dispatcher::start(std::function<void()> handler /* = {} */)
{
    while (true) {
        if (handler) {
            handler();
        }
    };
}

} // namespace es
