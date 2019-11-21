#include "Camera.h"
#include "Settings.h"

glm::vec3 Camera::cameraPos = glm::vec3(0.0f, 5.0f, -5.0f);
glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float Camera::yaw = 90.0f;
float Camera::pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;
float Camera::cameraSpeed = 15.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setup()
{
	//projMat = projection();
	glm::mat4 projMat = glm::perspective(fov, 1.0f, 0.1f, 1500.0f);
	//projMat = 
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "projMat"), 1, GL_FALSE, value_ptr(projMat));
}

void Camera::update(int deltaTime)
{
	//glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow)
		{
			glm::mat4 viewMat = glm::lookAt(
				GameEngine::gameobjects[i]->position + glm::vec3(-cos(radians(GameEngine::gameobjects[i]->rotate + 180)) * 10, 10, 
					-sin(radians(GameEngine::gameobjects[i]->rotate - 180)) * 10), 
				GameEngine::gameobjects[i]->position, 
				vec3(0, 1, 0));
		}
	}
	//glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "viewMat"), 1, GL_FALSE, value_ptr(viewMat));
}

void Camera::setMouseMove(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	//forces mouse to stay in the window
	int win_w = glutGet(GLUT_WINDOW_WIDTH);
	int win_h = glutGet(GLUT_WINDOW_HEIGHT);
	if (x < 100 || x > win_w - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
	else if (y < 100 || win_h - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
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
