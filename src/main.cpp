#include "../include/position.h"
#include "../include/config.h"
#include "../include/menu.h" 
#include <chrono>

int main() {
    Config config;

    if (!config.setPath()) return -1;
    if (!config.load()) std::cout << "[ERROR]: Failed to load saved positions." << "\n";
    if (!config.createCfg()) {
        std::cout << "[ERROR]: Failed to create lastsavedpos.cfg, make sure the path is correct." << "\n";
        return -1;
    }

    PositionManager position(config);
    if (!position.init()) {
        std::cout << "[ERROR]: Couldn't open the console.log file, make sure -condebug is in launch options." << "\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return -1;
    }

    Menu menu("momentum v0.1 (insert to show/hide)", 300, 250);
    if (!menu.create()) {
        std::cout << "[ERROR]: Failed to create the menu." << "\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return -1;
    }

    std::cout << "[Momentum]: Successfully started the application." << "\n";

    auto time = std::chrono::steady_clock::now();

    while (!menu.shouldClose()) {
        menu.render(config);

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - time).count() > 100) {
            position.run();
            time = now;
        }
    }

    menu.destroy();
    config.save();

    return 0;
}