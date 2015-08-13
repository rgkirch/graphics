GLEW = -lGLEW -lGLU -lGL
GLFW = -lglfw
INCLUDE = -I/usr/include
DEBUG = -g

first.exe: first.cpp
	g++ $(DEBUG) -o first.exe first.cpp $(INCLUDE) $(GLFW) $(GLEW)
