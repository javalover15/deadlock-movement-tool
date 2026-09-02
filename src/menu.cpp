#include "../include/menu.h"

static char buffer[128] = "";
static int positionIndex = 0;

static bool open = true;
static bool pressed = false;

void addNewPositon(Config& config, const std::string& name) {
	std::ifstream cfg(config.getPath() + "cfg\\lastsavedpos.cfg");

	if (!cfg.is_open()) {
		std::cout << "[ERROR]: Couldn't open lastsavedpos.cfg." << "\n";
		return;
	}

	std::string line;
	if (std::getline(cfg, line)) {
		std::stringstream stream(line);
		Position pos;
		if (stream >> pos.name >> pos.x >> pos.y >> pos.z) {
			pos.name = name;
			config.addPosition(pos);
		}
	}
	else {
		std::cout << "[ERROR]: There's no position saved in lastsavedpos.cfg." << "\n";
	}
}

Menu::Menu(const char* name, const int& width, const int& height) : name(name), width(width), height(height), window(nullptr) {
	flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
}

bool Menu::shouldClose() const {
	return this->window == nullptr ? true : glfwWindowShouldClose(this->window);
}

bool Menu::create() {
	std::cout << "[Momentum]: Creating application menu." << "\n";

	if (!glfwInit()) return false;

	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	int sWidth = mode->width;
	int sHeight = mode->height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(sWidth + 1, sHeight, this->name, nullptr, nullptr);
	if (this->window == nullptr) return false;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGL();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, sWidth + 1, sHeight);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = nullptr;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	return true;
}

void Menu::render(Config& config) {
	glfwPollEvents();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		open = !open;
		glfwFocusWindow(window);
		glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, open ? GLFW_FALSE : GLFW_TRUE);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	if (open) {
		ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(this->width, this->height), ImGuiCond_FirstUseEver);

		ImGui::Begin(name, &open, flags);

		ImGui::TextWrapped("saved positions");
		ImGui::BeginChild("positions_list", ImVec2(0, 100), true);
		for (int i = 0; i < config.getPositions().size(); i++) {
			Position position = config.getPositions()[i];
			bool selected = positionIndex == i;

			if (ImGui::Selectable(position.name.c_str(), selected)) {
				positionIndex = i;
			}
		}
		ImGui::EndChild();

		if (ImGui::InputText("new position", buffer, IM_COUNTOF(buffer))) {
			setPositionName(buffer);
		}

		if (ImGui::Button("set current position") && !config.getPositions().empty()) {
			Position position = config.getPositions()[positionIndex];
			config.setPosition("setpos " + std::to_string(position.x) + " " + std::to_string(position.y) + " " + std::to_string(position.z));
		}

		if (ImGui::Button("add new position")) {
			std::string name = getPositionName();

			if (!name.empty()) {
				std::replace(name.begin(), name.end(), ' ', '_');
				addNewPositon(config, name);
			}
		}

		if (ImGui::Button("delete current position")) {
			std::vector<Position>& positions = config.getPositions();
			if (!positions.empty()) {
				positions.erase(positions.begin() + positionIndex);
				positionIndex = (std::max)(positionIndex - 1, 0);
			}
		}

		ImGui::End();
		//if menu was closed with the 'X' instead of insert, stop the program
		if (!open) glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(this->window);
}

void Menu::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Menu::setPositionName(const std::string& name) {
	positionName = name;
}

std::string Menu::getPositionName() const {
	return positionName;
}