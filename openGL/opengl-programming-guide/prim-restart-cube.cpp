#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <stdio.h>
#include <math.h>

#include "../shader.hpp"

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
	Shader shader( "./primitive_restart.vs.glsl", "./primitive_restart.fs.glsl" );

    static const GLfloat cube_positions[] =
    {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f
    };
    static const GLfloat cube_colors[] =
    {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f
    };
    static const GLushort cube_indices[] =
    {
        0, 1, 2, 3, 6, 7, 4, 5,
        0xFFFF,
        2, 6, 0, 4, 1, 5, 3, 7
    };
    GLuint VBO;
	glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);
    GLuint EBO;
    glGenBuffers( 1, &EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW );
	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions) );

    glClearColor( 0.6f, 0.8f, 0.8f, 1.0f );




	glm::mat4 projection;
	projection = glm::perspective( 45.0f, (GLfloat)WIDTH/HEIGHT, 0.1f, 100.0f );

	// Game loop
	while( !glfwWindowShouldClose( window ) ) {
	//for( int iter = 1; iter; --iter ) {
		glfwPollEvents();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glUseProgram( shader.Program );
		glm::mat4 models[2];
		
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

        glBindVertexArray( VAO );
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        //glDrawArrays( GL_TRIANGLES, 0, 6 );
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
        //glBindVertexArray( 0 );
        glFlush();
		glfwSwapBuffers( window );
		fps();
		printf("\n");
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteBuffers( 1, &EBO );

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}
