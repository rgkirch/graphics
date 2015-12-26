#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <math.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void init(GLFWwindow* &theWindow, char* nameOfWindow, GLuint windowWidth, GLuint windowHeight);
GLchar* readFile(char* fileName);
GLuint createShader(char* vertexShaderFileName, char* fragmentShaderFileName);
void printShaderLog(char* errorMessageWithoutNewline, GLuint shaderProgram);
void checkShaderStepSuccess(GLint shaderProgramID, GLuint statusToCheck);

int main(int argc, char** argv) {
    if(argc < 3) {
        fprintf(stderr, "You have to run the program with at least two arguments.\n");
        fprintf(stderr, "./a.out vertexShaderFileName fragmentShaderFileName\n");
        fprintf(stderr, "exiting\n");
        return 1;
    }

    const GLuint WIDTH = 1920/2, HEIGHT = 1080/2;
    float aspect = float(HEIGHT) / float(WIDTH);
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);
    float t = glfwGetTime() / 10000.0f;
    GLFWwindow* window;
    init(window, argv[0], WIDTH, HEIGHT);

    GLuint shaderProgram = createShader(argv[1], argv[2]);
    glUseProgram(shaderProgram);

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

    glm::mat4 view;
    glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "view" ), 1, GL_FALSE, glm::value_ptr(view) );
	glm::mat4 projection;
	projection = glm::perspective( 45.0f, (GLfloat)WIDTH/HEIGHT, 0.1f, 100.0f );
    glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "projection" ), 1, GL_FALSE, glm::value_ptr(projection) );

	glEnable( GL_DEPTH_TEST );

	while( !glfwWindowShouldClose( window ) ) {
		glfwPollEvents();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBindVertexArray( VAO );
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        //glDrawArrays( GL_TRIANGLES, 0, 6 );
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
        //glFlush();
		glfwSwapBuffers( window );
	}

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
    char* sourceFileName[] = { vertexShaderFileName, fragmentShaderFileName };
    GLint shaderEnums[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
    GLuint program = glCreateProgram();
    if( ! program ) fprintf(stderr, "error: failed to create program\n");
    for(int i = 0; i < 2; ++i) {
        GLchar* shaderCode = readFile( sourceFileName[i] );
        GLuint shader = glCreateShader( shaderEnums[i] );
        glShaderSource( shader, 1, (const GLchar**)&shaderCode, NULL );
        glCompileShader(shader);
        checkShaderStepSuccess(shader, GL_COMPILE_STATUS);
        glAttachShader(program, shader);
        free( shaderCode );
        //delete [] shaderCode;
        glDeleteShader(shader);
    }
    glLinkProgram(program);
    checkShaderStepSuccess(program, GL_LINK_STATUS);
    return program;
}

void checkShaderStepSuccess(GLint program, GLuint status) {
    GLint success = -3;
    switch(status) {
        case GL_COMPILE_STATUS:
            glGetShaderiv( program, status, &success );
            if( success == -3 ) fprintf(stderr, "error: the success check may have a false positive\n");
            if( ! success ) {
                printShaderLog((char*)"error: gl shader program failed to compile.", program);
                fprintf(stderr, "Exiting.\n");
                exit(1);
            }
            break;
        case GL_LINK_STATUS:
            glGetProgramiv( program, status, &success );
            printf("success value %d\n", success);
            if( success == -3 ) fprintf(stderr, "error: the success check may have a false positive\n");
            if( ! success ) {
                printShaderLog((char*)"error: gl shader program failed to link.", program);
                //fprintf(stderr, "Exiting.\n");
                //exit(1);
            }
            break;
        default:
            fprintf(stderr, "function called with unhandled case.\n");
            break;
    }
}

void printShaderLog(char* errorMessage, GLuint shader) {
    fprintf(stderr, "%s\n", errorMessage);
    GLint length = 0;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );
    printf("log length %d\n", length);
    GLchar* logText = (GLchar*)malloc(sizeof(GLchar) * (length + 1));
    logText[length] = '\0';
    glGetShaderInfoLog(shader, length, &length, logText);
    printf("printing log\n");
    //fprintf(stderr, "%s", logText);
    cout << logText << endl;
    free(logText);
}

void init(GLFWwindow* &window, char* name, GLuint width, GLuint height) {
	/* Initialize the library */
	if ( !glfwInit() ) {
        fprintf(stderr, "GLFW failed to init.\n");
        fprintf(stderr, "Exiting.\n");
        exit(1);
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow( width, height, name, NULL, NULL );
	if ( !window ) {
		glfwTerminate();
        fprintf(stderr, "GLFW failed to create the window.\n");
        fprintf(stderr, "Exiting.\n");
        exit(1);
	}
	glfwMakeContextCurrent( window );

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
        fprintf(stderr, "GLEW failed to init.\n");
        fprintf(stderr, "Exiting.\n");
        exit(1);
	}

	glViewport( 0, 0, width, height );

    printf( "VENDOR = %s\n", glGetString( GL_VENDOR ) ) ;
    printf( "RENDERER = %s\n", glGetString( GL_RENDERER ) ) ;
    printf( "VERSION = %s\n", glGetString( GL_VERSION ) ) ;
}
