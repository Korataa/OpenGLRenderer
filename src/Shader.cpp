#include "../include/Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
{
	ID = NULL;
}

Shader::Shader(const std::string& vPath, const std::string& fPath)
{
	loadShaders(vPath, fPath);
}

void Shader::loadShaders(const std::string& vPath, const std::string& fPath)
{
	std::string vCode, fCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try
	{
		//open the files
		vShaderFile.open(vPath);
		fShaderFile.open(fPath);
		//read the files content into streams
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//then we clsoe the file handlers
		vShaderFile.close();
		fShaderFile.close();
		//convert stream to string
		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader->File was not read" << std::endl;
	}
	//have to do this because opengl doesnt take strings (i hate strings in c++)
	const char* vShaderSource = vCode.c_str();
	const char* fShaderSource = fCode.c_str();

	//now we compile the shaders
	int success;
	char infolog[512];

	//Vertex shader
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glCompileShader(vShader);
	//check for errors with the shader compile
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infolog);
		std::cout << "Shader->Vertex->Compilation failed" << std::endl;
	}

	//Fragment shader
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderSource, NULL);
	glCompileShader(fShader);
	//Check for errors with shader compile
	if (!success)
	{
		glGetShaderInfoLog(fShader, 512, NULL, infolog);
		std::cout << "Shader->Fragment->Compilation failed" << std::endl;
	}

	//now we link the shaders
	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	//Check for link errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		std::cout << "Shader->Program->Linking failed" << std::endl;
	}
	//we can delete the shaders now because they are already in use by the program
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value)	const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value)	const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}