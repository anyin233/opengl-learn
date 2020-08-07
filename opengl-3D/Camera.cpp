#include "Camera.h"

Camera::Camera(glm::vec3 pos, float screenX, float screenY, float sensitivity)
{
	this->view = glm::mat4(1.0f);
	this->proj = glm::mat4(1.0f);
	
	this->cameraPos = pos;
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//初始化Pos, Front, Up三要素

	this->lastMouseX = screenX / 2.0f;
	this->lastMouseY = screenY / 2.0f;//初始将鼠标放在屏幕中央
	this->sensitivity = sensitivity;
	
	this->firstMouse = true;

	this->pitch = 0.0f;
	this->yaw = -90.0f;//-90.0偏航角会直接指向Z轴负方向

	this->fov = 45.0;

	updateCameraFront();
	updateView();
	updateProj();
}

void Camera::updateCameraFront()
{
	float pitch = this->pitch;
	float yaw = this->yaw;
	glm::vec3 front = glm::vec3(1.0f);
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	this->cameraFront = glm::normalize(front);
}

void Camera::updateView()
{
	this->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateProj()
{
	this->proj = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastMouseY = ypos;
		lastMouseX = xpos;
		firstMouse = false;
	}

	float xOffset = xpos - lastMouseX;
	float yOffset = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	pitch += yOffset;
	yaw += xOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraFront();
	updateView();
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	updateProj();
}
