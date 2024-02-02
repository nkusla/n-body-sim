#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <iostream>
#include <vector>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Body.hpp"
#include "globals.hpp"

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
		glm::vec2 transformBodyPosition(glm::vec2 position);
		void displayBodies(std::vector<Body>& bodies);
		void checKeyPressed();
		void displayWidgets();
};

#endif