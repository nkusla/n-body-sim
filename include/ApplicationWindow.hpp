#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <iostream>
#include <vector>
#include <string.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Simulator.hpp"
#include "globals.hpp"
#include "DataParser.hpp"
#include "globals.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window;
		glm::vec2 screenSize;
		float scaling_factor = 1e-2;
		float scaling_step = 5e-4;
		bool simulationStopped = false;
		int selectedFile = 0;
		int selectedSolver = 0;

		std::shared_ptr<Simulator> simulator;

	public:
		static const char* fileOptions[];
		static const char* solverOptions[];

		ApplicationWindow(int width, int height);
		GLFWwindow* getWindow();
		void setSimulator(std::shared_ptr<Simulator> pSimulator);

		bool checkApplicationClose();
		void closeApplication();
		glm::vec2 transformBodyPosition(glm::vec2 position);
		void displayBodies();
		void checKeyPressed();
		void displayAllWidgets();
		void displayOptionsWidget(const char* name, const char* option[], int numOptions, int& selectedOption);
		void resetSimulator();
		void runFrame();
};

#endif