/*Libraries*/

//C++
#include <stdio.h>
#include <iostream>

//OpenGL
#include "main.h"


// TODO: LearnOpenGL: Hello-Window "Input"


int main(void)
{
	// Initialize GLFW and set to version 3.3
	// Tell GLFW to use Core-Profile to get access to smaller subset
	// of OpenGL features without backwards-compatible features we dont need. 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "FirstOpenGLWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set Size of Rendering Window (in pixels)
	glViewport(0, 0, 800, 600);

	// Registered to be called on every window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Create the render loop

	while (!glfwWindowShouldClose(window))
	{
		// swaps color buffer and shows as output to screen
		glfwSwapBuffers(window);

		// Checks if any events are triggered
		glfwPollEvents();
	}

	// Clean GLFW resources allocated
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}