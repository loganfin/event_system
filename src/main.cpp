#include "es/dispatcher.hpp"
#include "es/event.hpp"

#include <iostream>
#include <sstream>
#include <string>

// Only capable of moving in one dimension
struct Character {
    std::string name;
    int position = 0;

    explicit Character(std::string const& name) : name{name} {};

    void execute(std::string const& command)
    {
        if (command == "move") {
            std::cout << name << " is moving one space...\n";
            position += 1;
        } else {
            std::cout << "Unknown command.\n";
        }
    }
};

// Custom event created by the consumer of libes
struct CommandEvent : public es::Event {
    std::string character;
    std::string command;

    explicit CommandEvent(std::string const& input)
    {
        // Assume two tokens
        auto input_stream = std::stringstream{input};
        input_stream >> character >> command;
    }
};

int main()
{
    auto dispatcher = es::Dispatcher{};
    auto characters = std::vector<Character>{};
    auto command_buf = std::string{};

    characters.emplace_back("bob");
    characters.emplace_back("charlotte");

    dispatcher.subscribe<CommandEvent>([&characters](auto const& event) {
        auto valid_character = false;

        for (auto& character : characters) {
            if (character.name == event.character) {
                valid_character = true;
                character.execute(event.command);
            }
        }

        if (!valid_character) {
            std::cout << "Invalid character name.\n";
        }
    });

    // Try "bob move" and "charlotte move"
    dispatcher.start([&dispatcher, &command_buf]() {
        std::cout << "> ";
        std::getline(std::cin, command_buf);
        dispatcher.publish<CommandEvent>(command_buf);
    });
}
