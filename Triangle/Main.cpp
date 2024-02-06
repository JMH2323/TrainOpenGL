#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.08f, 0.4f, 0.8f, 1.0f);\n"
"}\n\0";


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	



	// Create a GLFWwindow object of 800 by 800 pixels, naming it "MyWindow"
	GLFWwindow* window = glfwCreateWindow(800, 800, "MyWindow", NULL, NULL);
	// Error check the window pointer
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD 
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);

	// Create vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile to Machine Code
	glCompileShader(vertexShader);

	// Create fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile to Machine Code
	glCompileShader(fragmentShader);

	// Create Shader Program Object 
	GLuint shaderProgram = glCreateProgram();
	// Attach Vertex and Fragment Shaders to the Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all the shaders together
	glLinkProgram(shaderProgram);

	// After Linking, delete the unneeded shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.7f * float(sqrt(3)) / 3, 0.0f, // Lower Left corner
		0.5f, -0.7f * float(sqrt(3)) / 3, 0.0f, // Lower Right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	// Create reference containers for Vertex Array Object and Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current bound object
	glBindVertexArray(VAO);
	// Bind the VBO by specifying it is a buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure attributes so OpenGL knows how to read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable attributes so OpenGL knows how to use them
	glEnableVertexAttribArray(0);

	// Bind both VBO and VAO to prevent modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	

	// Main while loop
    while(!glfwWindowShouldClose(window))
    {
		// Specify background color
		glClearColor(0.20f, 0.09f, 0.07f, 1.0f);
		// Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Swap back buffer with front buffer
		glUseProgram(shaderProgram);
		// Bind VAO so GL knows to use it
		glBindVertexArray(VAO);
		// Draw the Triangle using TRIANGLES Primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap Front-Back Buffers
		glfwSwapBuffers(window);

		// Do all Events
        glfwPollEvents();
    }


	// Clean Up
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;

}