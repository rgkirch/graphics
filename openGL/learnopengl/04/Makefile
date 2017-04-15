target = 
GLEW = -lGLEW -lGLU -lGL
GLFW = -lglfw
INCLUDE = -I/usr/include
DEBUG = -g

app.exe: $(target)
	g++ -std=c++11 $(DEBUG) -o app.exe $(target) $(INCLUDE) -I../../stb $(GLFW) $(GLEW)
