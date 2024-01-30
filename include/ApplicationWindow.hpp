#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Body.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window;

	public:
		ApplicationWindow(int width, int height);
		GLFWwindow* getWindow();

		bool checkApplicationClose();
		void closeApplication();
};

#endif