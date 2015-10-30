#include "glHelper.h"
#include <string>

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glHelper* window = new glHelper(1300, 1000, 10, 10);
	string filename = "img/4.bmp";
	string title = "Spherical Viewer";
	window->init(filename.c_str(), title.c_str());
	window->run();
	delete window;
	return 0;
}
