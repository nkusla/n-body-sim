#include "../include/ApplicationWindow.hpp"

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
}

GLFWwindow* ApplicationWindow::getWindow() { return window; }

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

void ApplicationWindow::displayBodies(std::vector<Body>& bodies) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(200.f * scaling_factor);
	glBegin(GL_POINTS);
		for(Body& b : bodies) {
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

void ApplicationWindow::displayWidgets() {
    static int selectedFile = 0;
	static int selectedSolver = 0;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(screenSize.x - 200, 0));
		ImGui::SetWindowSize(ImVec2(200, 300));

		ImGui::Text("Files");
    	if (ImGui::BeginCombo("##files", fileOptions[selectedFile])) {
			for (int i = 0; i < IM_ARRAYSIZE(fileOptions); i++) {
				const bool isSelected = (selectedFile == i);
				if (ImGui::Selectable(fileOptions[i], isSelected))
					selectedFile = i;

				// Set the initial focus on the selected option
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
    	}

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		ImGui::Text("Solvers");
    	if (ImGui::BeginCombo("##solvers", solverOptions[selectedSolver])) {
			for (int i = 0; i < IM_ARRAYSIZE(solverOptions); i++) {
				const bool isSelected = (selectedSolver == i);
				if (ImGui::Selectable(solverOptions[i], isSelected))
					selectedSolver = i;

				// Set the initial focus on the selected option
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
    	}

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		ImGui::Button("Stop");
		ImGui::SameLine();
		ImGui::Button("Reset");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}