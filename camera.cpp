#include "camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
				GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
	position_ = startPosition;
	worldUp_ = startUp;
	yaw_ = startYaw;
	pitch_ = startPitch;
	front_ = glm::vec3(0.0f, 0.0f, 1.0f);

	moveSpeed_ = startMoveSpeed;
	turnSpeed_ = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
	GLfloat velocity = moveSpeed_ * deltaTime;

	if (keys[GLFW_KEY_W]) {
		position_ += front_ * velocity;
	}
	if (keys[GLFW_KEY_S]) {
		position_ -= front_ * velocity;
	}
	if (keys[GLFW_KEY_A]) {
		position_ -= right_ * velocity;
	}
	if (keys[GLFW_KEY_D]) {
		position_ += right_ * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= turnSpeed_;
	yChange *= turnSpeed_;

	yaw_ += xChange;
	pitch_ += yChange;

	if (pitch_ > 89.0f) {
		pitch_ = 89.0f;
	}
	if (pitch_ < -89.0f) {
		pitch_ = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix() {
	return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::update() {
	front_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_.y = sin(glm::radians(pitch_));
	front_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_ = glm::normalize(front_);

	right_ = glm::normalize(glm::cross(front_, worldUp_));
	up_ = glm::normalize(glm::cross(right_, front_));
}

Camera::~Camera() {

}