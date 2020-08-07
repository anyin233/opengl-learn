#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader(std::string, std::string);
	void use();
	unsigned int ID;
};
