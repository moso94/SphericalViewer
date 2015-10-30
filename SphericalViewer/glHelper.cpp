#include "glHelper.h"

//Private Area--------------------------------------------------
glHelper *glHelper::glWindow = NULL;

void glHelper::updateCamera(bool isRotate, int lastX, int x, int lastY, int y)
{
	GLfloat xoffset = x - lastX;
	GLfloat yoffset = y - lastY;

	if (isRotate)
	{
		glWindow->get_camera()->set_yaw(xoffset * glWindow->MouseRotateSens);
		glWindow->get_camera()->set_roll(yoffset * glWindow->MouseRotateSens);
		glWindow->get_camera()->set_front();
	}
}

void glHelper::updateGlMatrices()
{
	auto cam = glWindow->get_camera();

	glm::vec3 pos = cam->get_pos();
	glm::vec3 front = pos + cam->get_front();
	glm::vec3 up = cam->get_up();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cam->get_aspect(), (GLdouble)glWindow->width / (GLdouble)glWindow->height, 10, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(front.x, front.y, front.z, pos.x, pos.y, pos.z, up.x, up.y, up.z);
	glScalef(-1, 1, -1);
}

void glHelper::reshape(int width, int height)
{
	auto cam = glWindow->get_camera();

	glWindow->width = width;
	glWindow->height = height;

	glViewport(0, 0, width, height);

	updateGlMatrices();
}

void glHelper::swapBuffers(void)
{
	glutSwapBuffers();
}

void glHelper::display()
{
	updateCamera(glWindow->isRotate, glWindow->mouse_oldX, glWindow->mouse_newX, glWindow->mouse_oldY, glWindow->mouse_newY);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, glWindow->_textureId);
	glPushMatrix();

	updateGlMatrices();

	gluSphere(glWindow->sphere, 50, 100, 100);

	glPopMatrix();
	glFlush();
	swapBuffers();
	glutPostRedisplay();
}

void glHelper::set_window(glHelper* window)
{
	glWindow = window;
}

camera* glHelper::get_camera()
{
	return cam;
}

void glHelper::mouseMotion(int x, int y)
{
	glWindow->mouse_newX = x;
	glWindow->mouse_newY = y;
}

void glHelper::mouseEvent(int button, int state, int x, int y)
{
	glWindow->isRotate = false;
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		glWindow->isRotate = true;
		break;
	case 3:
		glWindow->get_camera()->set_aspect(-glWindow->MouseZoomSens);
		break;
	case 4:
		glWindow->get_camera()->set_aspect(glWindow->MouseZoomSens);
		break;
	}

	if (glWindow->first)
	{
		glWindow->mouse_oldX = x;
		glWindow->mouse_oldX = y;
		glWindow->first = false;
	}

	if (state == GLUT_DOWN)
	{
		glWindow->mouse_oldX = x;
		glWindow->mouse_oldY = y;
		glWindow->mouse_newX = x;
		glWindow->mouse_newY = y;
	}
	else if (state == GLUT_UP)
	{
		glWindow->mouse_oldX = glWindow->mouse_newX;
		glWindow->mouse_oldY = glWindow->mouse_newY;
	}
}

//Public Area--------------------------------------------------
glHelper::glHelper(GLuint window_width, GLuint window_height, GLint window_x, GLint window_y) : MouseRotateSens(0.008f), MouseZoomSens(1.0f)
{
	set_window(this);
	posX = window_x;
	posY = window_y;
	width = window_width;
	height = window_height;
	mouse_oldX = 0;
	mouse_newX = 0;
	mouse_oldY = 0;
	mouse_newY = 0;
	isRotate = false;
	cam = new camera(window_width, window_height);
	cam->set_pos(0.0f, 0.0f, 0.0f);
	first = true;
}

void glHelper::run()
{
	glutMainLoop();
}

int glHelper::BindTexture(const char* fileName)
{

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);

	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);


	_textureId = loadTextureFromImage(fileName);

	if (_textureId == -1)
		return -1;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);

	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricOrientation(sphere, GLU_INSIDE);

	gluQuadricNormals(sphere, GLU_SMOOTH);

	return 0;
}

int glHelper::init(const char* fileName, const char* title)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(posX, posY);
	glutCreateWindow(title);
	glutDisplayFunc(glHelper::display);
	glutReshapeFunc(glHelper::reshape);
	glutMouseFunc(glHelper::mouseEvent);
	glutMotionFunc(glHelper::mouseMotion);
	glEnable(GL_DEPTH_TEST);
	return BindTexture(fileName);
}

glHelper::~glHelper()
{
	delete cam;
};