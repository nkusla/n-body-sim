#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Body.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window;
		glm::vec2 screenSize;
		float scaling_factor = 1e-2;
		float scaling_step = 1e-4;

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