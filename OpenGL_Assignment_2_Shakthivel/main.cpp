#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderGreenSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderYellowSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";



int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Shakthivel MURUGAVEL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);


	// Create Fragment Shader Object and get its reference
	GLuint fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);

	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShaderGreen, 1, &fragmentShaderGreenSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShaderGreen);

	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
	glCompileShader(fragmentShaderOrange);

	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
	glCompileShader(fragmentShaderYellow);

	// Create Shader Program Object and get its reference
	GLuint shaderProgramGreen = glCreateProgram();
	GLuint shaderProgramOrange = glCreateProgram();
	GLuint shaderProgramYellow = glCreateProgram();


	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgramGreen, vertexShader);
	glAttachShader(shaderProgramGreen, fragmentShaderGreen);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgramGreen);


	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);

	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderGreen);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderOrange);


	float lowerLeftTriangle[] = {

		0.0f,  1.0f, 0.0f, // Lower left corner
		-0.5f, 0, 0.0f, // Inner down
		0.5f, 0, 0.0f // Inner left
	};
	float lowerRightTriangle[] = {

		-0.5f, 0, 0.0f, // Inner down
		-1.0f,  -1.0f, 0.0f, // Lower right corner
		0.0f, -1.0, 0.0f // Inner right
	};
	float topTriangle[] = {

		0.5f, 0, 0.0f, // Inner left
		0.0f, -1.0, 0.0f, // Inner right
		1.0f, -1.0, 0.0f // Upper corner
	};


	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(topTriangle), topTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
		glUseProgram(shaderProgramGreen);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Unbind the VAO after drawing
		glBindVertexArray(0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the objects we've created
	glDeleteVertexArrays(3, VAO);
	glDeleteBuffers(3, VBO);
	glDeleteProgram(shaderProgramGreen);
	glDeleteProgram(shaderProgramYellow);
	glDeleteProgram(shaderProgramOrange);


	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}