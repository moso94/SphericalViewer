#include "camera.h"

camera::camera(GLuint width, GLuint height) : aspect_minimum(10.0f), aspect_maximum(90.0f), roll_minimum(-89.0f), roll_maximum(89.0f)
{
	up = glm::vec3(0.0f, 0.0f, 1.0f);
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 1.0f, 0.0f);

	_width = width;
	_height = height;

	_yaw = 0.0f;
	_roll = 0.0f;
	_aspect = aspect_maximum;
}

//Setters
void camera::set_front()
{
	front.x = -sin(glm::radians(_yaw)) * cos(glm::radians(_roll));
	front.y = cos(glm::radians(_yaw)) * cos(glm::radians(_roll));
	front.z = sin(glm::radians(_roll));
	front = glm::normalize(front);
}

void camera::set_aspect(GLfloat dAspect)
{
	_aspect += dAspect;

	if (_aspect > aspect_maximum)
		_aspect = aspect_maximum;

	if (_aspect < aspect_minimum)
		_aspect = aspect_minimum;

}

void camera::set_yaw(GLfloat dYaw)
{
	_yaw -= dYaw;
}

void camera::set_roll(GLfloat dRoll)
{
	_roll += dRoll;
	if (_roll > roll_maximum)
		_roll = roll_maximum;

	if (_roll < roll_minimum)
		_roll = roll_minimum;
}

void camera::set_pos(GLfloat x, GLfloat y, GLfloat z)
{
	pos = glm::vec3(x, y, z);
}

void camera::set_up(GLfloat x, GLfloat y, GLfloat z)
{
	up = glm::vec3(x, y, z);
}

//Getters
GLfloat camera::get_yaw()
{
	return _yaw;
}

GLfloat camera::get_roll()
{
	return _roll;
}

GLfloat camera::get_aspect()
{
	return _aspect;
}

glm::vec3 camera::get_front() const
{
	return front;
}

glm::vec3 camera::get_pos() const
{
	return pos;
}

glm::vec3 camera::get_up() const
{
	return up;
}