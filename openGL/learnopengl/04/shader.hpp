#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;

		std::ifstream vertexShaderInputFileStream;
		std::ifstream fragmentShaderInputFileStream;

		// ensures ifstream objects can throw exceptions:
		vertexShaderInputFileStream.exceptions (std::ifstream::badbit);
		fragmentShaderInputFileStream.exceptions (std::ifstream::badbit);
		try {
			// Open files
			vertexShaderInputFileStream.open(vertexPath);
			fragmentShaderInputFileStream.open(fragmentPath);

			std::stringstream vertexShaderStream, fragmentShaderStream;
			// Read file's buffer contents into streams
			vertexShaderStream << vertexShaderInputFileStream.rdbuf();
			fragmentShaderStream << fragmentShaderInputFileStream.rdbuf();

			// close file handlers
			vertexShaderInputFileStream.close();
			fragmentShaderInputFileStream.close();

			// Convert stream into string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		} catch (std::ifstream::failure e) {
			std::printf( "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			printf( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			printf( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			printf( "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	// Uses the current shader
	void useProgram() { 
		glUseProgram(this->Program); 
	}
};

#endif
