#include <fstream>
#include <iostream>
#include <toml++/toml.h>

int main() {
    toml::parse_result result;
    try {
        result = toml::parse_file("data/game.data");
        auto numbers = result["entity"]["id"];
        std::cout << "table has 'numbers': " << !!numbers << "\n";
        std::cout << "numbers is an: " << numbers.type() << "\n";
        std::cout << "numbers: " << numbers << "\n";

    } catch (const toml::parse_error &err) {
        std::cerr << "Parsing failed:\n"
                  << err << std::endl;
        return 1;
    }
}