#include "Camera.h"
#include "Settings.h"

glm::vec3 Camera::cameraPos;
glm::vec3 Camera::cameraFront;
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
	glm::mat4 projMat = glm::perspective(fov, 1.0f, 0.1f, 1500.0f);
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "projMat"), 1, GL_FALSE, value_ptr(projMat));
}

void Camera::update(int deltaTime)
{
	if (GraphicsEngine::cameraMode == 1)
	{
		for (int i = 0; i < GameEngine::gameobjects.size(); i++)
		{
			if (GameEngine::gameobjects[i]->objectToFollow)
			{
				cameraPos = GameEngine::gameobjects[i]->position + vec3(30 * cos(GameEngine::gameobjects[i]->rotate), 20, 30 * -sin(GameEngine::gameobjects[i]->rotate));
				cameraFront = GameEngine::gameobjects[i]->position;
			}
		}
		viewMat = glm::lookAt(cameraPos, cameraFront, cameraUp);
	}
	else
	{
		viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
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
	Camera::cameraPos += cameraSpeed * Camera::cameraFront;
	return 0;
}

int Camera::grDecelerate()
{
	Camera::cameraPos -= cameraSpeed * Camera::cameraFront;
	return 0;
}

int Camera::grTurnLeft()
{
	Camera::cameraPos -= glm::normalize(glm::cross(Camera::cameraFront, cameraUp)) * Camera::cameraSpeed;
	return 0;
}

int Camera::grTurnRight()
{
	Camera::cameraPos += glm::normalize(glm::cross(Camera::cameraFront, cameraUp)) * Camera::cameraSpeed;
	return 0;
}

int Camera::cameraSwitch()
{
	if (GraphicsEngine::cameraMode == 1) { 
		GraphicsEngine::cameraMode = 2; 	
		cameraPos = glm::vec3(0.0f, 5.0f, -5.0f); 
		cameraFront = glm::vec3(0.0f, 0.0f, 5.0f);
	}
	else { GraphicsEngine::cameraMode = 1; }
	return 0;
}