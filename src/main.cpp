#include "es/dispatcher.hpp"
#include "es/event.hpp"

#include <iostream>
#include <print>
#include <string>

// Capable of moving on a line
struct Character {
    std::string name;
    int position = 0;

    Character(std::string const& name) : name{name} {};

    void execute(std::string const& command)
    {
        if (command == "move") {
            position += 1;
        }
    }
};

struct CommandEvent : public es::Event {
    std::string command;

    CommandEvent(std::string const& command) : command{command} {}
};

void setup_game(es::Dispatcher& dispatcher)
{
    auto bob = Character{"bob"};

    // when a specific "command event" occurs, I want something to happen to bob

    dispatcher.subscribe<CommandEvent>([&bob](auto const& event) {
        std::cout << "moving one space\n";
        bob.execute(event.command);
    });
}

int main()
{
    std::println("Hello world");
    auto event = es::Event{};

    auto dispatcher = es::Dispatcher{};

    setup_game(dispatcher);

    auto command_buf = std::string{};

    dispatcher.start([&dispatcher, &command_buf]() {
        std::cout << "> ";
        std::getline(std::cin, command_buf);
        std::cout << "You entered: " << command_buf << std::endl;
        dispatcher.publish<CommandEvent>(command_buf);
    });
}
