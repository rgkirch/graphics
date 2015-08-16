target = 
GLEW = -lGLEW -lGLU -lGL
GLFW = -lglfw
INCLUDE = -I/usr/include
INCLUDE_STB = -I./stb
INCCLUDE_GLM = -I/usr/local/include
DEBUG = -g

app.exe: $(target)
	g++ $(DEBUG) -o app.exe $(target) $(INCLUDE) $(INCLUDE_STB) $(INCCLUDE_GLM)  $(GLFW) $(GLEW)
