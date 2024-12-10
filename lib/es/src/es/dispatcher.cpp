#include "es/dispatcher.hpp"

namespace es {

void Dispatcher::start(std::function<void()> handler)
{
    while (true) {
        handler();
    };
}

} // namespace es
