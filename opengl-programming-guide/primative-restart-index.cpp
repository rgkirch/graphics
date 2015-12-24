#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

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
    GLFWwindow* window;

	/* Initialize the library */
	if ( !glfwInit() ) {
		return -1;
	}

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

	//glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	//glDisable( GL_DEPTH_TEST );

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
        0xFFFF, // try !0
        2, 6, 0, 4, 1, 5, 3, 7
    };
    GLuint VBO;
	glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);
    GLuint EBO;
    glGenBuffers( 1, &EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW );
	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
    int shaderLayoutPosition = 0;
    int shaderLayoutColor = 1;
    glVertexAttribPointer( shaderLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glVertexAttribPointer( shaderLayoutColor, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(cube_positions) );
    glEnableVertexAttribArray( shaderLayoutPosition );
    glEnableVertexAttribArray( shaderLayoutColor );
	//glBindVertexArray( 0 );

    glClearColor( 0.6f, 0.8f, 0.8f, 1.0f );

	while( !glfwWindowShouldClose( window ) ) {
		glfwPollEvents();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBindVertexArray( VAO );
        //glDrawArrays( GL_TRIANGLES, 0, 3 );
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
        //glBindVertexArray( 0 );

        glFlush();
		glfwSwapBuffers( window );
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteBuffers( 1, &EBO );

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
            if( ! success ) printShaderLog((char*)"error: gl shader program failed to compile.", program);
            break;
        case GL_LINK_STATUS:
            glGetProgramiv( program, status, &success );
            printf("success bit %d\n", success);
            if( success == -3 ) fprintf(stderr, "error: the success check may have a false positive\n");
            if( ! success ) printShaderLog((char*)"error: gl shader program failed to link.", program);
            break;
        default:
            fprintf(stderr, "function called with unhandled case.\n");
            break;
    }
}

void printShaderLog(char* errorMessage, GLuint shader) {
    fprintf(stderr, "%s\n", errorMessage);
    printf("printing log\n");
    GLint length = -1;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );
    printf("log length %d\n", length);
    GLchar* logText = (GLchar*)malloc(sizeof(GLchar) * (length + 1));
    logText[length] = '\0';
    glGetShaderInfoLog(shader, length, &length, logText);
    //fprintf(stderr, "%s", logText);
    cout << logText << endl;
    free(logText);
}
