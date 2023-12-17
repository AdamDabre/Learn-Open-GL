#include "Camera.hpp"


Camera::Camera(CameraSettings settings, CameraProperties properties)
{
	this->properties.position = properties.position;
	this->properties.worldUp = properties.worldUp;
	this->properties.up = properties.up;
	this->properties.front = properties.front;
	this->properties.right = properties.right;

	this->settings.speed = settings.speed;
	this->settings.sensitivity = settings.sensitivity;
	this->settings.pitch = settings.pitch;
	this->settings.yaw = settings.yaw;
	this->settings.zoom = settings.zoom;

	updateCamera();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(this->properties.position, this->properties.position + this->properties.front, this->properties.up);
}

void Camera::move(Camera_Movement direction, float deltaTime)
{
	float velocity = settings.speed * deltaTime;
	if (direction == FORWARD)
		properties.position += properties.front * velocity;

	if (direction == BACKWARD)
		properties.position -= properties.front * velocity;

	if (direction == LEFT)
		properties.position -= properties.right * velocity;

	if (direction == RIGHT)
		properties.position += properties.right * velocity;

	if(direction == UP)
		properties.position += properties.up * velocity;

	if (direction == DOWN)
		properties.position -= properties.up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= settings.sensitivity;
	yoffset *= settings.sensitivity;

	settings.yaw += xoffset;
	settings.pitch += yoffset;

	// making sure that when pitch is out of bounds, screen doesn't get flipped
	const float maxPitch = 89.0f;
	const float minPitch = -89.0f;

	if (settings.pitchConstraint)
	{
		if (settings.pitch > maxPitch)
			settings.pitch = maxPitch;

		if (settings.pitch < minPitch)
			settings.pitch = minPitch;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCamera();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	const float minZoom = 1.0f;
	const float maxZoom = 45.0f;

	settings.zoom -= (float)yoffset;
	if (settings.zoom < minZoom)
		settings.zoom = minZoom;

	if (settings.zoom > maxZoom)
		settings.zoom = maxZoom;
}



void Camera::updateCamera()
{
		// Calcualte the new front vectors
	glm::vec3 front;
	front.x = cos(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));
	front.y = sin(glm::radians(settings.pitch));
	front.z = sin(glm::radians(settings.yaw)) * cos(glm::radians(settings.pitch));

	properties.front = glm::normalize(front);

		// recalualte the right and up vector
	properties.right = glm::normalize(glm::cross(properties.front, properties.worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	properties.up = glm::normalize(glm::cross(properties.right, properties.front));

}

Camera::Camera()
{
	this->settings = CameraSettings ();
	this->properties = CameraProperties ();
}

	// settings get and set
CameraSettings Camera::getCameraSettings() const
{
	return this->settings;
}

void Camera::setCameraSettings(const CameraSettings cameraSettings)
{
	this->settings = cameraSettings;
	updateCamera();
}

	// properties get and setters
CameraProperties Camera::getCameraProperties() const
{
	return this->properties;
}

void Camera::setCameraProperties(const CameraProperties cameraProperties)
{
	this->properties = cameraProperties;
	updateCamera();
}