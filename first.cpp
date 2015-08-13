#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const GLuint WIDTH = 800, HEIGHT = 600;

void error_callback( int error, const char* description )
{
	fprintf( stderr, "%s", description );
	//fputs( description, stderr );
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
}

const GLchar* vertexShaderSource = "#version 330 core\n"
	// declare inputs with the 'in' keyword
	// set the location to be used later
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

int main()
{
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

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		fprintf( stderr, "glewInit() failed\n" );
	}

	glViewport( 0, 0, WIDTH, HEIGHT );

	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

	// VERTEX SHADER
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	// void glShaderSource(	GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		printf( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog );
	}
	// FRAGMENT SHADER
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
	glCompileShader( fragmentShader );
	// Check for compile time errors
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		printf( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog );
	}
	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );
	// Check for linking errors
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
		printf( "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog );
	}
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		 0.5f,	0.5f, 0.0f	// Top	 
	};
	// vertex buffer object (VBO)
	// vertex array object (VAO)
	GLuint VBO, VAO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	// void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray( 0 ); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Game loop

	while( !glfwWindowShouldClose( window ) ) {
		glClear( GL_COLOR_BUFFER_BIT );
		glfwPollEvents();

		// Draw our first triangle
		glUseProgram( shaderProgram );
		glBindVertexArray( VAO );
		glDrawArrays( GL_TRIANGLES, 0, 3 );
		glBindVertexArray( 0 );

		glfwSwapBuffers( window );
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}
