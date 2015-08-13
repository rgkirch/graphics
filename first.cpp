#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void error_callback( int error, const char* description )
{
	fputs(description, stderr);
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if ( !glfwInit() )
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK )
	{
		//Problem: glewInit failed, something is seriously wrong.
		printf( "glewInit() failed, aborting.\n" );
	}

	glViewport(0, 0, 800, 600);

	glfwSetKeyCallback(window, key_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        /* Render here */

        glfwSwapBuffers(window);
    }

	glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}
