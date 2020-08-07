#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"
#include <windows.h>

#include <iostream>

float trans = 0.5f;
float size = 1.0f;

void processKey(GLFWwindow*);

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"vertexColor = gl_Position;\n"
"}";//顶点着色器源码

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main(){\n"
"FragColor = vertexColor;\n"
"}";

const char* secondFragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 nowColor;\n"
"void main(){\n"
"FragColor = nowColor;\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//初始化GLFW

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL-learning", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Cannot initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1920, 1080);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);//这里将上面代码中定义的顶点着色器代码和创建的的着色器对象绑定
	glCompileShader(vertex_shader);

	const unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragment_shader);

	const unsigned int second_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(second_fragment_shader, 1, &secondFragmentShaderSource, nullptr);
	glCompileShader(second_fragment_shader);

	const unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);//链接shader程序

	const unsigned int second_program = glCreateProgram();
	glAttachShader(second_program, vertex_shader);
	glAttachShader(second_program, second_fragment_shader);
	glLinkProgram(second_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(second_fragment_shader);

	float vertices[] = {
		//first triangle
		-0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	float secondVertices[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f
	};

	float squareVertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left
	};

	int index[]{
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAOs[2];
	unsigned int VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	const std::string fragment = R"(C:\\Users\\theny\\source\\repos\\opengl-learn2\\opengl-learn2\\fragmentShader.shader)";
	const std::string vertex = R"(C:\\Users\\theny\\source\\repos\\opengl-learn2\\opengl-learn2\\vertexShader.shader)";
	Shader shader(vertex, fragment);

	unsigned int VAO, VBO, EBO;
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int width, height, crChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("asset/img.png", &width, &height, &crChannels, 0);
	unsigned int texture[2];
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	int width2, height2, crChannels2;
	unsigned char* data2 = stbi_load("asset/img2.jpg", &width2, &height2, &crChannels2, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data2);

	Shader textureShader("vertexShaderWithTexture.shader", "fragmentShaderWithTexture.shader");

	textureShader.use();
	textureShader.setInt("texture1", 0);
	textureShader.setInt("texture2", 1);
	textureShader.setFloat("trans", trans);
	textureShader.setFloat("size", size);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	transform = glm::scale(transform, glm::vec3(1.0f, 0.5f, 0.2f));
	unsigned int transLoc = glGetUniformLocation(textureShader.shader, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

	while (!glfwWindowShouldClose(window)) {
		processKey(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);

		shader.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		double time = glfwGetTime();
		float redValue = (sin(time) / 2.0f) + 0.5f;
		int nowColorLocation = glGetUniformLocation(second_program, "nowColor");
		glUseProgram(second_program);
		glUniform4f(nowColorLocation, redValue, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		textureShader.use();
		textureShader.setFloat("trans", trans);
		textureShader.setFloat("size", size);
		transform = glm::translate(transform, glm::vec3(0.0005f, -0.0005f, 0.0f));
		transform = glm::rotate(transform, glm::radians(sin((float)glfwGetTime()) * 10.0f), glm::vec3(0.0, 0.0, 1.0));
		transLoc = glGetUniformLocation(textureShader.shader, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(10);
	}
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}

void processKey(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (trans < 1.0f) {
			trans += 0.01f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (trans > 0.0f) {
			trans -= 0.01f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		size += 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		size -= 0.1f;
	}
}