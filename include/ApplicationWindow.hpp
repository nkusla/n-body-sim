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
		std::vector<glm::vec2> positions;
		unsigned int positionBuffer;

	public:
		ApplicationWindow(int width, int height);
		GLFWwindow* getWindow();

		bool checkApplicationClose();
		void closeApplication();
		void extractAndTransformPosition(std::vector<Body>& bodies);
		void displayBodies(std::vector<Body>& bodies);
};

#endif