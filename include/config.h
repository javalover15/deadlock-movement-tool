#pragma once

#include "include.h"

struct Position {
	std::string name;
	double x;
	double y;
	double z;
};

class Config {
private:
	std::vector<Position> positions;
	//later make a function that automatically finds deadlock path
	std::string path;
public:
	bool setPath();
	std::string getPath() const;

	bool save() const;
	bool load();
	bool createCfg();

	void addPosition(const Position&);
	void removePosition(const std::string&);
	
	std::vector<Position>& getPositions();
	Position* getPosition(const std::string&);

	void setPosition(const std::string&);
};