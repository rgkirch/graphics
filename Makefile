target = main.cpp
GLEW = -lGLEW -lGLU -lGL
GLFW = -lglfw
INCLUDE = -I/usr/include
INCLUDE_STB = -I./stb
DEBUG = -g

app.exe: $(target)
	g++ $(DEBUG) -o app.exe $(target) $(INCLUDE) $(INCLUDE_STB) $(GLFW) $(GLEW)
