#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct CameraSettings
{
	float yaw = -90.0f;
	float pitch = 0.0f;
	float speed = 2.5f;
	float sensitivity = 0.1f;
	float zoom = 45.0f;

	bool pitchConstraint = true;
};

struct CameraProperties
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldUp =  glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
};

class Camera
{
public:


	Camera();
	Camera(CameraSettings settings, CameraProperties properties);

	glm::mat4 getViewMatrix() const;

	void move(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

	CameraSettings getCameraSettings() const;
	void setCameraSettings(const CameraSettings cameraSettings);

	CameraProperties getCameraProperties() const;
	void setCameraProperties(const CameraProperties cameraProperties);

private:
	void updateCamera();
	CameraSettings settings;
	CameraProperties properties;
};