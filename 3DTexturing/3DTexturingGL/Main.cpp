

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"




// Vertices coordinates       // Vertices Colors          // Texture Coordinates
GLfloat vertices[] =
{
	-0.5f, 0.0f,  0.5f,         0.83f, 0.70f, 0.44f,    0.15f, 0.0f, // Forward Left Corner
	-0.5f, 0.0f, -0.5f,         0.83f, 0.70f, 0.44f,    1.0f, 0.0f, // Forward Right Corner
	 0.5f, 0.0f, -0.5f,         0.83f, 0.70f, 0.44f,    0.25f, 0.0f, // ForeGround Right Corner
	 0.5f, 0.0f,  0.5f,         0.83f, 0.70f, 0.44f,    1.0f, 0.0f, // ForeGround Left Corner
	 0.0f, 0.8f,  0.0f,         0.92f, 0.86f, 0.76f,    0.5f,  1.0f  // Top
};

// Indices for vertex generation order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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

	Texture ChefCat("Chef.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	ChefCat.texUnit(shaderProgram, "tex0", 0);


	// Model values
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	////// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.20f, 0.09f, 0.07f, 1.0f);
		// Clean back buffer and assign new color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader to use
		shaderProgram.Activate();

		// Rotate the model in its 3D glory
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}


		// Initialize Matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);


		
		

		// Apply transformations to matrices
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		// Clipping objects too close or too far
		proj = glm::perspective(glm::radians(45.0f), (float)(800/800), 0.01f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assign a value to the uniform
		glUniform1f(uniID, 0.5f);
		// Bind Texture Object
		ChefCat.Bind();
		// Bind VAO so GL knows to use it
		VAO1.Bind();
		// Draw the Triangle using TRIANGLES Primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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