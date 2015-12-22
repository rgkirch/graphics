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

using namespace std;

GLchar* readFile(char* fileName);
GLuint createShader(char* vertexShaderFileName, char* fragmentShaderFileName);
void printShaderLog(char* errorMessageWithoutNewline, GLuint shaderProgram);
int checkShaderStepSuccess(GLint shaderProgramID, GLint statusToCheck);

int main(int argc, char** argv) {
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

	int count;

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		fprintf( stderr, "glewInit() failed\n" );
	}

	glViewport( 0, 0, WIDTH, HEIGHT );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );

    GLuint shaderProgram = createShader(argv[1], argv[2]);

    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, vertexShaderCode },
        { GL_FRAGMENT_SHADER, fragmentShaderCode },
        { GL_NONE, NULL }
    };
    //GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &((GLchar*)vertexShaderString.c_str()), NULL);

	GLfloat vertices[] = {
		-1.0f, -1.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f
	};
    GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
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

		glActiveTexture( GL_TEXTURE );
		glBindTexture(GL_TEXTURE_2D, texture);
		//glUniform1i( glGetUniformLocation(shaderProgram, "texture"), 0 );

		//glUseProgram( shaderProgram );

		glm::mat4 models[2];
		
        glBindVertexArray( VAO );
        //glDrawArrays( GL_TRIANGLES, 0, 3 );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );

		glfwSwapBuffers( window );
		printf("\n");
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
    contents[fileLength] = '\0';
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
    for(int i = 0; i < 2; ++i) {
        GLchar* shaderCode = readFile( code[i] );
        GLuint shader = glCreateShader( shaders[i] );
        glShaderSource( shader, 1, &code[i], NULL );
        free( code[i] );
        //delete [] code[i];
        glCompileShader(shader);
        checkShaderStepSuccess(shader, GL_COMPILE_STATUS);
        glAttachShader(program, shader);
        glDeleteShader(shader);
    }
    glLinkProgram(program);
    checkShaderStepSuccess(program, GL_LINK_STATUS);
    return program;
}

int checkShaderStepSuccess(GLint program, GLint status) {
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
    GLint logLength;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
    GLchar* logText = (GLchar*)malloc(logLength + 1);
    logText[logLength] = '\0';
    glGetShaderInfoLog(shader, logLength, NULL, logText);
    fprintf(stderr, "%s\n", logText);
    free(logText);
}
