#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Body.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window;
		glm::vec2 screenSize;
		float scaling_factor = 1e-3;
		float scaling_step = 5e-6;

	public:
		ApplicationWindow(int width, int height);
		GLFWwindow* getWindow();

		bool checkApplicationClose();
		void closeApplication();
		glm::vec2 transformPosition(glm::vec2 position);
		void displayBodies(std::vector<Body>& bodies);
		void checKeyPressed();
};

#endif