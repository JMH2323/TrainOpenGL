

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"




////// Vertices coordinates		 // Vertices Colors		// Texture Coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,			 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,			 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,			 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,			 1.0f, 1.0f, 1.0f,		1.0f, 0.0f  // Lower right corner
};

// Indices for vertice generation order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};




////// Main

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidental modifying 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	////// Texture

	Texture ChefCat("Chef.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ChefCat.texUnit(shaderProgram, "tex0", 0);

	////// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.20f, 0.09f, 0.07f, 1.0f);
		// Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader to use
		shaderProgram.Activate();
		// Assign a value to the uniform
		glUniform1f(uniID, 0.5f);
		// Bind Texture Object
		ChefCat.Bind();
		// Bind VAO so GL knows to use it
		VAO1.Bind();
		// Draw the Triangle using TRIANGLES Primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap Front-Back Buffers
		glfwSwapBuffers(window);

		// Do all Events
		glfwPollEvents();
	}


	// Clean Up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ChefCat.Delete();
	shaderProgram.Delete();

	// Delete window and stop GLFW before ending program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}