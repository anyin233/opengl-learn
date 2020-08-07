#include "Shader.h"

#include <iostream>

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
	std::ifstream vertex_file;
	std::ifstream fragment_file;
	std::string vertex_string;
	std::string fragment_string;

	try
	{
		vertex_file.open(vertex_path);
		fragment_file.open(fragment_path);
		std::stringstream vertex_stream;
		std::stringstream fragment_stream;
		vertex_stream << vertex_file.rdbuf();
		fragment_stream << fragment_file.rdbuf();
		vertex_string = vertex_stream.str();
		fragment_string = fragment_stream.str();
	}
	catch (std::exception& e)
	{
		std::cout << "Cannot Open Shader File:" << e.what() << std::endl;
	}

	unsigned int vertex_shader, fragment_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vertex_code = vertex_string.c_str();
	const char* fragment_code = fragment_string.c_str();
	int success;
	char infoLog[512];

	glShaderSource(vertex_shader, 1, &vertex_code, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE::" << infoLog << std::endl;
	}

	glShaderSource(fragment_shader, 1, &fragment_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE::" << infoLog << std::endl;
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex_shader);
	glAttachShader(this->ID, fragment_shader);
	glLinkProgram(this->ID);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::use()
{
	glUseProgram(this->ID);
}