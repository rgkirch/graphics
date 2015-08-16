#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include "shader.hpp"

const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat cursorPositionX = 0;
GLfloat cursorPositionY = 0;

void error_callback( int error, const char* description )
{
	fprintf( stderr, "%s", description );
	//fputs( description, stderr );
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	cursorPositionX = xpos;
	cursorPositionY = ypos;
	//printf( "%f %f\n", xpos, ypos );
}

void fps() {
	static GLuint frames = 0;
	static GLfloat fpsTimeout = 0.0f;
	if( fpsTimeout == 0.0f ) {
		fpsTimeout = glfwGetTime() + 1.0f;
	}
	if( glfwGetTime() > fpsTimeout ) {
		fpsTimeout = glfwGetTime() + 1.0f;
		printf( "%d fps\n", frames);
		frames = 0;
	}
	++frames;
}

int main() {
	// INIT
	GLFWwindow* window;

	glfwSetErrorCallback( error_callback );

	/* Initialize the library */
	if ( !glfwInit() ) {
		return -1;
	}

	// must use exactly version 3
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow( WIDTH, HEIGHT, "Hello World", NULL, NULL );
	if ( !window ) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent( window );

	glfwSetKeyCallback( window, key_callback );
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		fprintf( stderr, "glewInit() failed\n" );
	}

	glViewport( 0, 0, WIDTH, HEIGHT );

	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

	// SHADER
	Shader shader( "./vertexShader.glsl", "./fragmentShader.glsl" );







	// Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
    };
    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
	// vertex buffer object (VBO)
	// vertex array object (VAO)
	GLuint VAO, VBO, EBO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &EBO );
	// BIND the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray( VAO );
		glBindBuffer( GL_ARRAY_BUFFER, VBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

		// void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		// the 0 for index comes from location = 0 in the vertex shader
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0 );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)) );
		glEnableVertexAttribArray( 0 );
		glEnableVertexAttribArray( 1 );
	glBindVertexArray( 0 );








	stbi_set_flip_vertically_on_load(1);
	// TEXTURE
    GLuint texture;
    glGenTextures(1, &texture);
	//printf( "texture: %d\n", texture );
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int width, height, comp;
    unsigned char* image = stbi_load("./images/container.jpg", &width, &height, &comp, 3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    GLuint texture1;
    glGenTextures(1, &texture1);
	//printf( "texture1: %d\n", texture1 );
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    image = stbi_load("./images/awesomeface.png", &width, &height, &comp, 3 );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);









	// Game loop
	while( !glfwWindowShouldClose( window ) ) {
		glClear( GL_COLOR_BUFFER_BIT );
		glfwPollEvents();

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i( glGetUniformLocation(shader.Program, "texture"), 0 );

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i( glGetUniformLocation(shader.Program, "texture1"), 1 );

		glUseProgram( shader.Program );


		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::rotate( model, glm::radians(cursorPositionX - WIDTH/2), glm::vec3(0.0f, 1.0f, 0.0f) );
		model = glm::rotate( model, glm::radians(cursorPositionY - HEIGHT/2), glm::vec3(1.0f, 0.0f, 0.0f) );
		view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );
		projection = glm::perspective( 45.0f, (GLfloat)WIDTH/HEIGHT, 0.1f, 100.0f );
		glUniformMatrix4fv( glGetUniformLocation(shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr(model) );
		glUniformMatrix4fv( glGetUniformLocation(shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr(view) );
		glUniformMatrix4fv( glGetUniformLocation(shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr(projection) );


		glBindVertexArray( VAO );
		//glDrawArrays( GL_TRIANGLES, 0, 3 );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );

		glfwSwapBuffers( window );
		fps();
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}
