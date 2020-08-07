#include "shader.h"

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexStream;
	std::ifstream fragmentStream;
	vertexStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vertexStream.open(vertexShaderPath);
		fragmentStream.open(fragmentShaderPath);
		std::stringstream vertexBuf, fragmentBuf;
		vertexBuf << vertexStream.rdbuf();
		fragmentBuf << fragmentStream.rdbuf();
		vertexStream.close();
		fragmentStream.close();
		vertexCode = vertexBuf.str();
		fragmentCode = fragmentBuf.str();
	}
	catch (std::exception e) {
		std::cout << "ERROR::READING_FILE_FAIL::" << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	int success;
	char infolog[512];

	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::COMPILE::VERTEX\n" << infolog << std::endl;
	}

	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::COMPILE::FRAGMENT\n" << infolog << std::endl;
	}

	this->shader = glCreateProgram();
	glAttachShader(this->shader, vertexShader);
	glAttachShader(this->shader, fragmentShader);
	glLinkProgram(this->shader);
	std::cout << glGetError() << std::endl;
	glGetShaderiv(this->shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->shader, 512, NULL, infolog);
		std::cout << "ERROR::LINK::PROGRAM\n" << infolog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	std::cout << glGetError() << std::endl;
}

void Shader::use() {
	glUseProgram(this->shader);
}

void Shader::setInt(std::string name, int val) {
	glUniform1i(glGetUniformLocation(this->shader, name.c_str()), val);
}

void Shader::setFloat(std::string name, float val) {
	glUniform1f(glGetUniformLocation(this->shader, name.c_str()), val);
}

void Shader::bindTexture(GLenum type, GLuint texture) {
	glBindTexture(type, texture);
}