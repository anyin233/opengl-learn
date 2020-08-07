#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
	Camera(glm::vec3);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	
private:
	glm::mat4 view;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float pitch;
	float yaw;
};

