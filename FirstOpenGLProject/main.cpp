/*Libraries*/

//C++
#include <stdio.h>
#include <iostream>

//OpenGL
#include "main.h"

// TODO - Fragment Shader Section

int main(void)
{
	// vertex shader source code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";


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

    // specify vertices for a triangle 
	// Note: these vertices need to be in Normalized Device Coordinates (NDC)
	// x,y,z values between -1.0 and 1.0
	// Any coordinate that falls outside this range will be discarded/clipped
	// and wont be visible on your screen
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Create a vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copies previously defined vertex data into buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// TODO - Read "Vertex Shader" on Hello-Triangle

	// Create vertex shader object
	unsigned int vertexShader = createVertexShader(vertexShaderSource);

	// Create fragment shader object
	unsigned int fragmentShader = createFragmentShader(fragmentShaderSource);

	// Create shader program
	unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader);

	// Activate Shader Program
	glUseProgram(shaderProgram);

	// delete shader objects, no longer need them after linking to program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set Size of Rendering Window (in pixels)
	glViewport(0, 0, 800, 600);

	// Registered to be called on every window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Create the render loop

	while (!glfwWindowShouldClose(window))
	{
		// Checks for input from the specified window
		processInput(window);

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swaps color buffer and shows as output to screen
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

unsigned int createVertexShader(const char* vertexShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if shader compilation was successfull
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertexShader;
}

unsigned int createFragmentShader(const char* fragmentShaderSource)
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

	}

	return fragmentShader;
}

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for shader program success
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderProgram;
}
