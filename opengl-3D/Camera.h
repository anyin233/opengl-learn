#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
	Camera(glm::vec3, float, float, float);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void updateCameraFront();
	void updateView();
	void updateProj();
	
	glm::mat4 getView()
	{
		return this->view;
	};
	glm::mat4 getProj()
	{
		return this->proj;
	}
	
private:
	
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float pitch;
	float yaw;
	float lastMouseX;
	float lastMouseY;
	float sensitivity;
	float fov;
	bool firstMouse;
};

