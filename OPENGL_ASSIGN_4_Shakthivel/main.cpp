#include "shader.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Shakthivel MURUGAVEL TP4", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shaderOrange("C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shader.vs", "C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shaderOrange.fs");
	Shader shaderGradient("C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shader.vs", "C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shaderGradient.fs");
	Shader shaderGreenBlack("C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shader.vs", "C:\\Users\\Shakthi\\Desktop\\SHAKTHI\\ESIEE\\ECOLE\\E5\\P2\\INF-5204C - Computer Graphics and Open GL\\TP4\\OPENGL_ASSIGN_4_Shakthivel\\shaderGreenBlack.fs");


	float lowerLeftTriangle[] = {

		-1.0f,  1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		-0.5f,  0.0f, 0.0f
	};
	float lowerRightTriangle[] = {

		 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	float topTriangle[] = {

		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};


	// Create reference containers for the Vartex Array Object, 
	// the Vertex Buffer Object, and the Element Buffer Object
	GLuint VAO[3], VBO[3];

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO[0]);
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(lowerLeftTriangle), lowerLeftTriangle, GL_STATIC_DRAW);
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lowerRightTriangle), lowerRightTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(topTriangle), topTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			break;  // Exit the loop if 'e' is pressed
		}
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderOrange.use();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shaderGradient.use();
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shaderGreenBlack.use();
		glBindVertexArray(VAO[2]);
		double  timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		int vertexColorLocation = glGetUniformLocation(shaderGreenBlack.ID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the objects we've created
	glDeleteVertexArrays(3, VAO);
	glDeleteBuffers(3, VBO);
	glDeleteProgram(shaderOrange.ID);
	glDeleteProgram(shaderGradient.ID);
	glDeleteProgram(shaderGreenBlack.ID);



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}