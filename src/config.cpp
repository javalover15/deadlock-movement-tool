#include "../include/config.h"

std::string inputPath() {
	std::string s;
	std::cout << "Game Path: ";
	std::getline(std::cin >> std::ws, s);
	return s;
}

bool Config::setPath() {
	std::ifstream in("positions.txt");

	if (in.is_open()) {
		std::string line;
		if (std::getline(in, line) && line.starts_with("path: ")) {
			this->path = line.substr(6);
		}
	}

	if (this->path.empty()) {
		this->path = inputPath();
	}

	if (!this->path.empty() && this->path.back() != '\\' && this->path.back() != '/') {
		this->path += "\\game\\citadel\\";
	}

	return true;
}

std::string Config::getPath() const {
	return path;
}

bool Config::save() const {
	std::ofstream file("positions.txt");
	if (!file.is_open()) return false;

	file << "path: " << path << "\n";

	for (const Position& pos : positions) {
		file << pos.name << " " << pos.x << " " << pos.y << " " << pos.z << "\n";
	}

	return true;
}

bool Config::load() {
	std::cout << "[Momentum]: Loading saved positions." << "\n";

	std::ifstream file("positions.txt");
	if (!file.is_open()) return false;

	positions.clear();

	std::string line;
	while (std::getline(file, line)) {
		if (line.starts_with("path: ")) continue;

		std::stringstream stream(line);
		Position pos;

		if (stream >> pos.name >> pos.x >> pos.y >> pos.z) {
			addPosition(pos);
		}
	}

	return true;
}

bool Config::createCfg() {
	std::cout << "[Momentum]: Creating lastsavedpos.cfg." << "\n";

	std::ofstream file(path + "cfg\\lastsavedpos.cfg");
	if (!file.is_open()) return false;

	return true;
}

void Config::addPosition(const Position& position) {
	Position* pos = getPosition(position.name);
	if (pos != nullptr) {
		std::cout << "Position with the name \"" + position.name + "\" already exists." << '\n';
		return;
	}

	positions.push_back(position);
}

void Config::removePosition(const std::string& name) {
	int index = -1;
	for (int i = 0; i < positions.size(); i++) {
		if (positions[i].name == name) {
			index = i;
			break;
		}
	}

	if (index != -1) positions.erase(positions.begin() + index);
}

std::vector<Position>& Config::getPositions() {
	return positions;
}

Position* Config::getPosition(const std::string& name) {
	for (Position& p : positions) {
		if (p.name == name) return &p;
	}
	return nullptr;
}

void Config::setPosition(const std::string& command) {
	std::ofstream cfg(path + "cfg\\lastsavedpos.cfg");

	if (!cfg.is_open()) {
		std::cout << "[ERROR]: Couldn't open lastsavedpos.cfg." << "\n";
		return;
	}

	cfg << command;
}