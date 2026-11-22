#include <exception>
#include <iostream>

#include "Game.h"

int main(int /*argc*/, char* /*argv*/[]) {
    try {
        Game game;
        game.run();
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
