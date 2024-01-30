#include "../include/ApplicationWindow.hpp"

ApplicationWindow::ApplicationWindow(int width, int height) {
	if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	screenSize = {width, height};
	window = glfwCreateWindow(width, height, "N body simulation", NULL, NULL);

	if(window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
    	std::cout << "Failed to initialize GLEW!" << std::endl;
    	return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// glGenBuffers(1, &positionBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(0);
}

GLFWwindow* ApplicationWindow::getWindow() { return window; }

bool ApplicationWindow::checkApplicationClose() {
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}

void ApplicationWindow::closeApplication() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void ApplicationWindow::extractAndTransformPosition(std::vector<Body>& bodies) {
	positions.clear();

	// ??????
	for(Body& b : bodies)
		positions.push_back(
			b.getPosition() / screenSize
		);
}

void ApplicationWindow::displayBodies(std::vector<Body>& bodies) {
	extractAndTransformPosition(bodies);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(5.f);
	glBegin(GL_POINTS);
		for(glm::vec2& pos : positions) {
			glVertex2f(pos.x, pos.y);
		}
	glEnd();
}