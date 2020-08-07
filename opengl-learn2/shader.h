#pragma once
#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

class Shader {
public:
	unsigned int shader;
	void use();
	void setInt(std::string, int);
	void setFloat(std::string, float);
	void bindTexture(GLenum, GLuint);
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

private:
};
#endif // !SHADER_H
