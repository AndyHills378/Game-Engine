#include "Camera.h"

glm::vec3 Camera::cameraPos = glm::vec3(0.0f, 5.0f, -5.0f);
glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float Camera::yaw = 90.0f;
float Camera::pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;
float Camera::cameraSpeed = 0.5f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setup()
{
	//projMat = projection();
	glm::mat4 projMat = glm::perspective(40.0f, 1.0f, 0.1f, 100.0f);
	//projMat = 
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "projMat"), 1, GL_FALSE, value_ptr(projMat));
}

void Camera::update()
{
	//glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "viewMat"), 1, GL_FALSE, value_ptr(viewMat));
}

int Camera::grAccelerate()
{
	cameraPos += cameraSpeed * cameraFront;
	return 0;
}

int Camera::grDecelerate()
{
	cameraPos -= cameraSpeed * cameraFront;
	return 0;
}

int Camera::grTurnLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return 0;
}

int Camera::grTurnRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return 0;
}
