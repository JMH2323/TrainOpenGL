#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices coordinates								// Vertices Colors
GLfloat vertices[] =
{
	-0.5f, -0.7f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.1f, 0.8f, // Lower Left corner
	 0.5f, -0.7f * float(sqrt(3)) / 3, 0.0f,		0.2f, 0.1f, 0.2f, // Lower Right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2/3, 0.0f,		1.0f, 0.1f, 1.0f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.9f, 0.1f, 0.9f, // Inner Left
	 0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.5f, 0.1f, 0.5f, // Inner right
	 0.0f, -1.4f * float(sqrt(3)) / 6, 0.0f, 		0.6f, 0.1f, 0.6f// Inner down
};

// Indices for vertice generation order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

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

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidental modifying 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");




	// Main while loop
    while(!glfwWindowShouldClose(window))
    {
		// Specify background color
		glClearColor(0.20f, 0.09f, 0.07f, 1.0f);
		// Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader to use
		shaderProgram.Activate();
		// Assign a value to the uniform
		glUniform1f(uniID, 0.5f);
		// Bind VAO so GL knows to use it
		VAO1.Bind();
		// Draw the Triangle using TRIANGLES Primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap Front-Back Buffers
		glfwSwapBuffers(window);

		// Do all Events
        glfwPollEvents();
    }


	// Clean Up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window and stop GLFW before ending program.
    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;

}