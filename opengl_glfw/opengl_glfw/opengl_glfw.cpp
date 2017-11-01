
#include "stdafx.h"
#include <GL/glew.h>		
#include <GLFW/glfw3.h> 
#include <iostream>


void window_resized(GLFWwindow* window, int width, int height);
void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void show_glfw_error(int error, const char* description);


int main()
{
	// A call-back function for handling error
	glfwSetErrorCallback(show_glfw_error);

	/* Initialize the library */
	if (!glfwInit()) {
		std::cerr << "GLFW 초기화 실패" << '\n';
		exit(-1);
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(
		800, // width
		600, // height
		"OpenGL Example",
		NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create a window" << '\n';
		glfwTerminate();
		exit(-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Call-back functions handling resizing windows & key events
	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, key_pressed);


	glfwSwapInterval(1);


	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW 초기화 실패 " << glewGetErrorString(err) << '\n';
		glfwTerminate();
		exit(-1);
	}


	std::cout << glGetString(GL_VERSION) << '\n';


	int nr_extensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nr_extensions);

	for (int i = 0; i < nr_extensions; ++i) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << '\n';
	}


	glClearColor(0, 0, 1, 1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {

		// Clear buffer prior to rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the front & the back buffers
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	glfwDestroyWindow(window);


	glfwTerminate();
	return 0;
}

void show_glfw_error(int error, const char* description) {
	std::cerr << "Error: " << description << '\n';
}

void window_resized(GLFWwindow* window, int width, int height) {
	std::cout << "Window resized, new window size: " << width << " x " << height << '\n';

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ( (key == 'Q' || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
		glfwTerminate();
		exit(0);
	}
}