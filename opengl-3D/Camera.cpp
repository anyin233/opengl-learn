#include "Camera.h"

Camera::Camera(glm::vec3 pos)
{
	this->view = glm::mat4(1.0f);
	this->cameraPos = pos;
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//��ʼ��Pos, Front, Up��Ҫ��

	this->pitch = 0.0f;
	this->yaw = -90.0f;//-90.0ƫ���ǻ�ֱ��ָ��Z�Ḻ����
}
