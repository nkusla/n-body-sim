#include <iostream>
#include <random>
#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DirectSimulator.hpp"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

int main() {

	std::default_random_engine generator(42);
  	std::uniform_real_distribution<double> distribution(-1.0,1.0);

	std::vector<Body> bodies(N_BODIES);

	for(int i = 0; i < N_BODIES; ++i) {
		bodies[i].setPosition({distribution(generator), distribution(generator)});
	}

	if(!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Simulator", NULL, NULL);

	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_POINTS);

		for(int i = 0; i < bodies.size(); i++) {
			glm::vec2 pos = bodies[i].getPosition();
			glVertex2f(pos.x, pos.y);
		}
		glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glfwTerminate();

	return 0;
}