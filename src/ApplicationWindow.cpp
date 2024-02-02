#include "../include/ApplicationWindow.hpp"

const char* ApplicationWindow::fileOptions[] = {
	"2_body",
	"2_body_orbit",
	"4_body",
	"galaxy"
};

const char* ApplicationWindow::solverOptions[] = {
	"SemiImplicitEuler",
	"ForwardEuler",
	"Verlet"
};

const char* ApplicationWindow::simulatorOptions[] = {
	"Direct simulator",
	"Barnes-Hut simulator"
};

std::vector<std::shared_ptr<Simulator>> ApplicationWindow::simulators;

std::vector<std::shared_ptr<Solver>> ApplicationWindow::solvers;

ApplicationWindow::ApplicationWindow(int width, int height) {
	if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	screenSize = {width, height};
	window = glfwCreateWindow(width, height, "N-body simulator", NULL, NULL);

	if(window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	simulator = simulators[0];
}

GLFWwindow* ApplicationWindow::getWindow() { return window; }

std::shared_ptr<Simulator> ApplicationWindow::getSimulator() {
	return simulator;
}

void ApplicationWindow::setSimulator(std::shared_ptr<Simulator> pSimulator) { simulator = pSimulator; }

bool ApplicationWindow::checkApplicationClose() {
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}

void ApplicationWindow::closeApplication() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

glm::vec2 ApplicationWindow::transformBodyPosition(glm::vec2 position) {
	return position * scaling_factor;
}

void ApplicationWindow::displayBodies() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(200.f * scaling_factor);
	glBegin(GL_POINTS);
		for(Body& b : simulator->getBodies()) {
			glm::vec2 pos = transformBodyPosition(b.getPosition());
			glVertex2f(pos.x, pos.y);
		}
	glEnd();
}

void ApplicationWindow::checKeyPressed() {
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		scaling_factor -= scaling_step;
		scaling_factor = (scaling_factor < 0) ? scaling_step : scaling_factor;
	}
	else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		scaling_factor += scaling_step;
	else
		return;
}

void ApplicationWindow::displayAllWidgets() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("##Control", nullptr, ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(screenSize.x - 200, 0));
	ImGui::SetWindowSize(ImVec2(200, 270));

	std::string nBodies = "N bodies: " + std::to_string(simulator->getBodies().size());
	ImGui::Text(nBodies.c_str());
	ImGui::Spacing(); ImGui::Spacing();
	std::string scaling = "Scaling facator: " + std::to_string(scaling_factor);
	ImGui::Text(scaling.c_str());

	ImGui::Separator();

	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Simulators");
	displayOptionsWidget("##simulators", simulatorOptions,
		sizeof(simulatorOptions)/sizeof(simulatorOptions[0]), selectedSimulator);

	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Files");
	displayOptionsWidget("##files", fileOptions,
		sizeof(fileOptions)/sizeof(fileOptions[0]), selectedFile);

	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Solvers");
	displayOptionsWidget("##solvers", solverOptions,
		sizeof(solverOptions)/sizeof(solverOptions[0]), selectedSolver);

	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	if(ImGui::Button("Play/Stop"))
		simulationStopped = !simulationStopped;

	ImGui::SameLine();
	if(ImGui::Button("Reset"))
		resetSimulator();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ApplicationWindow::displayOptionsWidget(const char* name, const char* options[], int numOptions, int& selectedOption) {
	if (ImGui::BeginCombo(name, options[selectedOption])) {
		for (int i = 0; i < numOptions; i++) {
			const bool isSelected = (selectedOption == i);
			if (ImGui::Selectable(options[i], isSelected)) {
				selectedOption = i;
				resetSimulator();
			}

			// Set the initial focus on the selected option
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void ApplicationWindow::resetSimulator() {
	simulator = simulators[selectedSimulator];
	simulator->resetSimulation();
	std::string path = "../data/" + std::string(fileOptions[selectedFile]) + ".csv";
	DataParser::readBodyDataFromCSV(path, simulator->getBodies());

	simulator->setSolver(solvers[selectedSolver]);
}

void ApplicationWindow::runFrame() {
	displayBodies();
	displayAllWidgets();

	if(!simulationStopped)
		simulator->simulateStep();

	glfwSwapBuffers(window);
	glfwPollEvents();
};