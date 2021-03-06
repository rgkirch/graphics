#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <stdio.h>
#include <math.h>

#include "shader.hpp"

#define PI 3.1415926

const GLuint WIDTH = 1920/2, HEIGHT = 1080/2;
GLFWwindow* window;
GLfloat aspectRatio = WIDTH / HEIGHT;
GLfloat mouseSensitivityRatio = aspectRatio;
GLfloat mouseSensitivity = 0.05f;
glm::vec2 mousePosition(0.0f, 0.0f);
glm::vec2 mouseScrollOffset( 0.0f, -30.0f );
glm::quat cameraOrientation;
glm::mat4 camera[2];
GLboolean keyboardKeys[1024] = {GL_FALSE};
GLboolean keyboardScancodes[1024] = {GL_FALSE};
glm::vec3 position(0.0f, 0.0f, 0.0f);
glm::vec3 direction(0.0f, 0.0f, 0.0f);
glm::vec3 rotation(0.0f, 0.0f, 0.0f);
glm::mat4 view;

void error_callback( int error, const char* description ) {
	fprintf( stderr, "%s", description );
	//fputs( description, stderr );
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if( key > 1023 ) {
		fprintf( stderr, "key input %d too large", key );
		key = 1023;
	}
	if( scancode > 1023 ) {
		fprintf( stderr, "scancode input %d too large", scancode );
		scancode = 1023;
	}
	if( action == GLFW_PRESS ) {
		keyboardKeys[key] = GL_TRUE;
		keyboardScancodes[scancode] = GL_TRUE;
		if( key == GLFW_KEY_ESCAPE ) {
			glfwSetWindowShouldClose( window, GL_TRUE );
		}
	} else if( action == GLFW_RELEASE ) {
		keyboardKeys[key] = GL_FALSE;
		keyboardScancodes[scancode] = GL_FALSE;
	}
}

GLfloat normalizeCursorMovement( GLfloat movement, GLfloat range ) {
	return (movement - floor(movement/range)*range)/range;
}

/*
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	//cameraOrientation = glm::rotate( cameraOrientation, (GLfloat)((xpos - mousePosition.x) * mouseSensitivity * mouseSensitivityRatio), glm::vec3(0.0f, 1.0f, 0.0f) );
	//cameraOrientation = glm::rotate( cameraOrientation, (GLfloat)((ypos - mousePosition.y) * mouseSensitivity * mouseSensitivityRatio), glm::vec3(1.0f, 0.0f, 0.0f) );
	camera[0] = glm::rotate( camera[0], glm::radians((GLfloat)((xpos - mousePosition.x) * mouseSensitivity * mouseSensitivityRatio)), glm::vec3(0.0f, 1.0f, 0.0f) );
	camera[1] = glm::rotate( camera[1], glm::radians((GLfloat)((ypos - mousePosition.y) * mouseSensitivity * mouseSensitivityRatio)), glm::vec3(1.0f, 0.0f, 0.0f) );
	direction.x += sin( (GLfloat)((mousePosition.x) * mouseSensitivity * mouseSensitivityRatio) );
	direction.z += cos( (GLfloat)((mousePosition.x) * mouseSensitivity * mouseSensitivityRatio) );
	//direction.x += cos( glm::radians((GLfloat)((ypos - mousePosition.y) * mouseSensitivity * mouseSensitivityRatio)) );
	direction = glm::normalize( direction );
	mousePosition.x = xpos;
	mousePosition.y = ypos;
	//printf( "%f %f\n", cameraOrientation[0], cameraOrientation[1] );
	//printf( "%f %f\n", xpos, ypos );
}
*/


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	//printf( "%d\n", (int)mouseScrollOffset[1] );
}


void fps() {
	static GLuint frames = 0;
	static GLfloat fpsTimeout = 0.0f;
	if( fpsTimeout == 0.0f ) {
		fpsTimeout = glfwGetTime() + 1.0f;
	}
	if( glfwGetTime() > fpsTimeout ) {
		fpsTimeout = glfwGetTime() + 1.0f;
		//printf( "%d fps\n", frames);
		frames = 0;
	}
	++frames;
}
void updateCamera() {
	// TODO handle overflow, can use glfwSetCursorPos
	double xpos, ypos;
	xpos = ypos = 0;
	glfwGetCursorPos( window, &xpos, &ypos );
	//GLfloat xdelta = xpos - mousePosition.x;
	//GLfloat ydelta = ypos - mousePosition.y;
	//mousePosition.x = xpos;
	//mousePosition.y = ypos;
	GLfloat temp;
	temp = normalizeCursorMovement( xpos, WIDTH * 4 ) * 2 * PI;
	rotation.y = temp;
	direction.x = sin( temp );
	direction.z = -cos( temp );
	temp = normalizeCursorMovement( ypos, WIDTH * 4 ) * 2 * PI;
	rotation.x = temp;
	printf( "direction x %f, y %f, z %f\n", direction.x, direction.y, direction.z );
	
	glm::mat4 tempMat;
	if( keyboardKeys[GLFW_KEY_W] ) {
		view = glm::translate( view, -1.0f * direction);
	}
	if( keyboardKeys[GLFW_KEY_S] ) {
		view = glm::translate( view, direction);
	}
	if( keyboardKeys[GLFW_KEY_A] ) {
		view = glm::translate( view, glm::vec3( direction.x, direction.y, direction.z) );
	}
	if( keyboardKeys[GLFW_KEY_D] ) {
	}
	if( keyboardKeys[GLFW_KEY_Q] ) {
	}
	if( keyboardKeys[GLFW_KEY_E] ) {
	}
}

int main() {
	// INIT

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
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	int count;
	//printf( "%s\n", glfwGetVideoModes( glfwGetPrimaryMonitor(), &count ) );

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		fprintf( stderr, "glewInit() failed\n" );
	}

	glViewport( 0, 0, WIDTH, HEIGHT );

	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
	glEnable( GL_DEPTH_TEST );

	// SHADER
	Shader shader( "./vertexShader.glsl", "./fragmentShader.glsl" );







	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
	};
    GLuint indices[] = {
		0, 1, 2,
		1, 2, 3,
		1, 3, 5,
		3, 5, 7,
		4, 5, 7,
		4, 6, 7,
		0, 4, 6,
		0, 2, 6,
		2, 3, 7,
		2, 6, 7,
		0, 1, 5,
		0, 4, 5
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







	glm::mat4 projection;
	projection = glm::perspective( 45.0f, (GLfloat)WIDTH/HEIGHT, 0.1f, 100.0f );

	/*
	for( int y = 0; y < 4; ++y ) {
		for( int x = 0; x < 4; ++x ) {
			printf( "%f ", test[x][y] );
		}
		printf("\n");
	}
	*/

	// Game loop
	while( !glfwWindowShouldClose( window ) ) {
	//for( int iter = 1; iter; --iter ) {
		glfwPollEvents();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


		glActiveTexture( GL_TEXTURE0 );
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i( glGetUniformLocation(shader.Program, "texture"), 0 );

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i( glGetUniformLocation(shader.Program, "texture1"), 1 );

		glUseProgram( shader.Program );


		glm::mat4 models[2];
		
		
		models[0] = glm::translate( models[0], glm::vec3( 4.0f, 4.0f, -10.0f ) );
		//models[1] = glm::translate( models[1], glm::vec3( -4.0f, -4.0f, -10.0f ) );
		models[1] = glm::scale( models[1], glm::vec3( 50.0f, 50.0f, 50.0f ) );

		updateCamera();
		//glm::mat4 rotatedView = camera[1] * camera[0] * view;
		printf( "rotation x %f, y %f, z %f\n", rotation.x, rotation.y, rotation.z );
		glm::mat4 rotatedView;
		rotatedView = glm::rotate( rotatedView, rotation.x, glm::vec3(1, 0, 0) ) ;
		rotatedView = glm::rotate( rotatedView, rotation.y, glm::vec3(0, 1, 0) ) ;
		rotatedView = glm::rotate( rotatedView, rotation.z, glm::vec3(0, 0, 1) ) ;
		rotatedView *= view;
		//view = glm::translate( view, position );
		//glm::mat4 rotatedView;
		
		//projection = glm::rotate( projection, glm::radians(cameraOrientation[1]), glm::vec3(1.0f, 0.0f, 0.0f) );
		//projection = glm::rotate( projection, glm::radians(cameraOrientation[0]), glm::vec3(0.0f, 1.0f, 0.0f) );
		//projection = projection * (cameraPosition / 10.0f);
		glUniformMatrix4fv( glGetUniformLocation(shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr(rotatedView) );
		glUniformMatrix4fv( glGetUniformLocation(shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr(projection) );

		for( int numBoxes = 0; numBoxes < 3; ++numBoxes ) {
			glUniformMatrix4fv( glGetUniformLocation(shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr(models[numBoxes]) );
			glBindVertexArray( VAO );
			//glDrawArrays( GL_TRIANGLES, 0, 3 );
			glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
			glBindVertexArray( 0 );
		}

		glfwSwapBuffers( window );
		fps();
		printf("\n");
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}
