#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <stdio.h>

#include <math.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "LoadShaders.h"

using namespace std;

GLchar* readFile(char* fileName);
GLuint createShader(char* vertexShaderFileName, char* fragmentShaderFileName);
void printShaderLog(char* errorMessageWithoutNewline, GLuint shaderProgram);
void checkShaderStepSuccess(GLint shaderProgramID, GLuint statusToCheck);

int main(int argc, char** argv) {
    if('\0' == EOF) {
        printf("equal\n");
    } else {
        printf("not equal\n");
    }
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main() {\n"
            "gl_Position = vec4( position, 1.0 );\n"
        "}\n";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
            "color = vec4(0.1f, 0.2f, 0.5f, 1.0f);\n"
        "}\n";

    if(argc < 3) {
        fprintf(stderr, "You have to run the program with at least two arguments.\n");
        fprintf(stderr, "./a.out vertexShaderFileName fragmentShaderFileName\n");
        fprintf(stderr, "exiting\n");
        return 1;
    }

    const GLuint WIDTH = 1920/2, HEIGHT = 1080/2;
    GLFWwindow* window;

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
	window = glfwCreateWindow( WIDTH, HEIGHT, argv[0], NULL, NULL );
	if ( !window ) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent( window );

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		fprintf( stderr, "glewInit() failed\n" );
	}

	glViewport( 0, 0, WIDTH, HEIGHT );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	//glEnable( GL_DEPTH_TEST );

    GLuint shaderProgram = createShader(argv[1], argv[2]);
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "./vertexShader.glsl" },
        { GL_FRAGMENT_SHADER, "./fragmentShader.glsl" },
        { GL_NONE, NULL }
    };
    //GLuint shaderProgram = LoadShaders(shaders);
    

    /*
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
    */

    
    glUseProgram(shaderProgram);

    const GLfloat vertex_positions[] =
    {
        -1.0f, -1.0f, 0.2f,
         1.0f,  0.0f, 0.2f,
         0.0f,  1.0f, 0.2f
    };
	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
    GLuint VBO;
	glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW );
    //GLint shaderVerticies = glGetUniformLocation(shaderProgram, "position");
    GLint shaderVerticies = 0;
    //printf("shader position location %d\n", shaderVerticies);
    glEnableVertexAttribArray( shaderVerticies );
    glVertexAttribPointer( shaderVerticies, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0 );
	glBindVertexArray( 0 );


    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	while( !glfwWindowShouldClose( window ) ) {
		glfwPollEvents();
		glClear( GL_COLOR_BUFFER_BIT );

        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );

		glfwSwapBuffers( window );
        //glFlush();
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}

// allocates memory for (shader) file contents
GLchar* readFile(char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if( ! file ) fprintf(stderr, "error: Could not open file %s\n", fileName);
    long fileLength = 0;
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    rewind(file);
    GLchar* contents = (GLchar*)malloc(fileLength + 1);
    if( ! contents ) fprintf(stderr, "error: Could not allocate memory.\n");
    contents[fileLength] = EOF;
    fread(contents, 1, fileLength, file);
    fclose(file);
    return contents;
}

GLuint createShader(char* vertexShaderFileName, char* fragmentShaderFileName) {
    if( ! vertexShaderFileName ) fprintf(stderr, "error: NULL passed in for vertex shader file name.\n");
    if( ! fragmentShaderFileName ) fprintf(stderr, "error: NULL passed in for fragment shader file name.\n");
    char* code[] = { vertexShaderFileName, fragmentShaderFileName };
    GLint shaders[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
    GLuint program = glCreateProgram();
    if( ! program ) fprintf(stderr, "error: failed to create program\n");
    printf("program id %u\n", program);
    for(int i = 0; i < 2; ++i) {
        const GLchar* shaderCode = readFile( code[i] );
        GLuint shader = glCreateShader( shaders[i] );
        glShaderSource( shader, 1, &shaderCode, NULL );
        glCompileShader(shader);
        checkShaderStepSuccess(shader, GL_COMPILE_STATUS);
        glAttachShader(program, shader);
        //free( shaderCode );
        delete [] shaderCode;
        //glDeleteShader(shader); //TODO uncomment this line
    }
    glLinkProgram(program);
    checkShaderStepSuccess(program, GL_LINK_STATUS);
    return program;
}

void checkShaderStepSuccess(GLint program, GLuint status) {
    GLint success = 0;
    glGetShaderiv( program, status, &success );
    char* errorMessage = NULL;
    if( ! success ) {
        switch(status) {
            case GL_COMPILE_STATUS:
                errorMessage = (char*)"error: gl shader program failed to compile.";
                break;
            case GL_LINK_STATUS:
                errorMessage = (char*)"error: gl shader program failed to link.";
                break;
            default:
                errorMessage = (char*)"error";
                break;
        }
        printShaderLog(errorMessage, program);
    }
}

void printShaderLog(char* errorMessage, GLuint shader) {
    fprintf(stderr, "%s\n", errorMessage);
    GLint length;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );
    fprintf(stderr, "log length %d\n", length);
    GLchar* logText = (GLchar*)malloc(sizeof(GLchar) * (length + 1));
    logText[length] = '\0';
    glGetShaderInfoLog(shader, length, &length, logText);
    fprintf(stderr, "length after? %d\n", length);
    cout << logText << endl;
    free(logText);
}
