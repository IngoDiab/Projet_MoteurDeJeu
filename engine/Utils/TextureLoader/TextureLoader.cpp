#include "TextureLoader.h"

#include "common/stb_image.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <stdexcept>

unsigned char* loadImage(const std::string& _path, int& _width, int& _height, int& _channels, const int _forceChannel)
{
	return stbi_load(_path.c_str(), &_width, &_height, &_channels, _forceChannel);
}

void freeImage(unsigned char* _image)
{
	stbi_image_free(_image);
}

GLuint loadTexture2DFromFilePath(const std::string& path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 3);
	if (!data) {
		stbi_image_free(data);
		throw std::runtime_error("Failed to load texture: " + path);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	setDefaultTexture2DParameters(texture);
	return texture;
}

GLuint loadTextureCubeMap2DFromFilePath(const std::vector<std::string>& path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	for(unsigned int _indexTexture = 0; _indexTexture < path.size(); ++_indexTexture)
	{
		unsigned char* data = stbi_load(path[_indexTexture].c_str(), &width, &height, &channels, 3);
		if (!data) {
			stbi_image_free(data);
			throw std::runtime_error("Failed to load texture cubemap: " + path[_indexTexture]);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + _indexTexture, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	setDefaultTextureCubemapParameters(texture);
	return texture;
}

void setDefaultTexture2DParameters(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

void setDefaultTextureCubemapParameters(GLuint texture) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}