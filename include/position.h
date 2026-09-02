#pragma once

#include "include.h"
#include "config.h"

class PositionManager {
private:
	Config& config;
	std::ifstream file;
public:
	PositionManager(Config&);
	bool init();
	void run();
};