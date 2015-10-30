#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <glm/glm.hpp>

class camera
{
	const float aspect_minimum;
	const float aspect_maximum;
	const float roll_minimum;
	const float roll_maximum;

	GLfloat	_yaw;
	GLfloat	_pitch;
	GLfloat _roll;
	GLfloat _aspect;
	GLuint	_width;
	GLuint	_height;
	glm::vec3   pos;
	glm::vec3	front;
	glm::vec3	up;

public:
	camera(GLuint, GLuint);
	~camera(){};

	//Setters
	void set_pos(GLfloat, GLfloat, GLfloat);
	void set_up(GLfloat, GLfloat, GLfloat);
	void set_aspect(GLfloat);
	void set_yaw(GLfloat);
	void set_roll(GLfloat);
	void set_front();

	//Getters
	glm::vec3	get_up() const;
	glm::vec3	get_pos() const;
	glm::vec3	get_front() const;
	GLfloat		get_yaw();
	GLfloat		get_roll();
	GLfloat		get_aspect();
};

#endif