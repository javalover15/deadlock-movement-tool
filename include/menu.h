#pragma once

#include "config.h"
#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_glfw.h"
#include "../external/imgui/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <windows.h>

class Menu {
private:
	GLFWwindow* window;
	ImGuiWindowFlags flags;
	const char* name;
	int width;
	int height;

	std::string positionName;
	Position currentPosition;
public:
	Menu(const char*, const int&, const int&);
	bool shouldClose() const;
	bool create();
	void render(Config&);
	void destroy();

	void setPositionName(const std::string&);
	std::string getPositionName() const;
};