#include "../include/position.h"

std::string savePos(const std::string& line) {
    std::stringstream stream(line);

    std::string a;
    std::string b;
    std::string c;

    double x;
    double y;
    double z;

    stream >> a >> b >> c >> x >> y >> z;

    return "setpos " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
}

PositionManager::PositionManager(Config& config) : config(config) {
}

bool PositionManager::init() {
    std::cout << "[Momentum]: Initializing position manager." << "\n";
    
    this->file.open(config.getPath() + "console.log");

    if (!this->file.is_open()) return false;

    //make sure we start reading from the last line of the console.log so we dont use old setpos commands
    file.seekg(0, std::ios::end);
    return true;
}

void PositionManager::run() {
    std::string line;
    while (std::getline(this->file, line)) {
        if (line.find(" setpos_exact ") != std::string::npos) {
            std::string command = savePos(line);
            config.setPosition(command);
        }
    }

    //clear getline error and continue reading from the bottom
    this->file.clear();
}