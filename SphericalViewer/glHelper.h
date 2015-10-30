#ifndef GL_HELPER_H
#define GL_HELPER_H
#include "camera.h"
#include "textureLoader.h"

using namespace std;

class glHelper
{
	const float MouseRotateSens;
	const float MouseZoomSens;

	camera *cam;
	GLuint width;
	GLuint height;
	GLint mouse_oldX;
	GLint mouse_oldY;
	GLint mouse_newX;
	GLint mouse_newY;
	GLint posX;
	GLint posY;
	bool isRotate;
	bool first;

	GLuint _textureId;
	GLUquadricObj *sphere;

	static glHelper* glWindow;
	static void updateCamera(bool, int, int, int, int);
	static void mouseEvent(int, int, int, int);
	static void mouseMotion(int, int);

	static void updateGlMatrices();
	static void reshape(int, int);
	static void display(void);
	static void swapBuffers();
	camera* get_camera();
	static void set_window(glHelper*);

public:
	glHelper(GLuint, GLuint, GLint, GLint);
	~glHelper();

	int BindTexture(const char*);
	int init(const char*, const char*);
	void run();



};

#endif 