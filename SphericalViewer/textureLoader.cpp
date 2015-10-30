#include "textureLoader.h"

GLuint loadTextureFromImage(const char* fileName)
{
	int width, height, channel;
	unsigned char* data = SOIL_load_image(fileName, &width, &height, &channel, SOIL_LOAD_RGBA);
	if (data && channel == 4)
	{
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		return textureId;
	}
	return -1;
}